#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "parse.h"

static uint8_t usb_rxcmd_ev_encoding_var[] = {
    0,
    USB_RXCMD_EV_ENCODING_RXACTIVE,
    USB_RXCMD_EV_ENCODING_HOSTDISCONNECT,
    USB_RXCMD_EV_ENCODING_RXACTIVE | USB_RXCMD_EV_ENCODING_RXERROR
};

static char *usb_header_type_strings[] = {
    "None",
    "Event",
    "Data",
    "RxCmd"
};

char *usb_get_header_type(int type)
{
    if((type >= 0) && (type < 4)) {
        return usb_header_type_strings[type];
    }
    return NULL;
}

struct usb_raw_s {
    uint8_t *buf;
    uint32_t len;
    struct usb_raw_s *next;
};

struct usb_data_s {
    uint8_t type;
    uint8_t val;
    uint64_t ts;
    struct usb_data_s *next;
};

struct usb_packet_s {
    uint8_t type;
    uint8_t *buf;
    uint32_t len;
    uint64_t ts;
    struct usb_packet_s *next;
};

struct usb_session_s {
    uint8_t *buf;
    uint32_t len;
    uint64_t ts;
    uint8_t last_event;
    struct usb_data_s data_list;
    struct usb_data_s *last_data;
    struct usb_data_s *last_data_decoded;
    struct usb_data_s *last_data_read;
    struct usb_packet_s packet_list;
    struct usb_packet_s *last_packet;
    struct usb_packet_s *last_packet_read;
    struct usb_raw_s raw_list;
    struct usb_raw_s *last_raw;
};

static void decode_data(struct usb_session_s *s)
{
    struct usb_data_s *d = s->last_data_decoded;
    uint8_t *buf, *p;
    uint32_t len;
    uint8_t ev_encoding;

    buf = malloc(2048);
    p = buf;
    len = 0;

    while(d->next){
        d = d->next;

        switch(d->type){
            case USB_HEADER_TYPE_NONE:
                break;
            case USB_HEADER_TYPE_EVENT:
                // printf("%ld:\tEvent: %02x\n", d->ts, d->val);
                s->last_event = d->val;
                break;
            case USB_HEADER_TYPE_DATA:
                *p++ = d->val;
                len++;
                //printf(" %02x",  d->val);
                break;
            case USB_HEADER_TYPE_RXCMD:
                ev_encoding = usb_rxcmd_ev_encoding_var[USB_RXCMD_EV_ENCODING(d->val)];
                if(!(ev_encoding & USB_RXCMD_EV_ENCODING_RXACTIVE)){
                    if(len){
                        s->last_packet->next = malloc(sizeof(struct usb_packet_s));
                        s->last_packet = s->last_packet->next;
                        memset(s->last_packet, 0, sizeof(struct usb_packet_s));
                        s->last_packet->buf = malloc(len);
                        memcpy(s->last_packet->buf, buf, len);
                        s->last_packet->len = len;
                        s->last_packet->ts = d->ts;
                        p = buf;
                        len=0;
                        s->last_data_decoded = d;
                    }
                    //printf("\n");
                }
        }
    }

    free(buf);
}

void usb_add_data(struct usb_session_s *s, uint8_t *buf, uint32_t buflen)
{
    uint8_t *p, *tmp;
    uint32_t len;
    uint8_t type = 0;
    uint8_t header_len = 0;
    uint64_t ts = 0;
    uint8_t required;
    int i;

    if(!buflen) {
        return;
    }

    /* keep raw buffers for file save */
    s->last_raw->next = malloc(sizeof(struct usb_raw_s));
    s->last_raw = s->last_raw->next;
    memset(s->last_raw, 0, sizeof(struct usb_raw_s));
    s->last_raw->buf = malloc(buflen);
    memcpy(s->last_raw->buf, buf, buflen);
    s->last_raw->len = buflen;
    // printf("stored (%d) %p\n", s->last_raw->len, s->last_raw->buf);

    if(!s->buf) {
        s->buf = malloc(buflen);
        memcpy(s->buf, buf, buflen);
        s->len = buflen;
    } else {
        s->buf = realloc(s->buf, s->len + buflen);
        memcpy(s->buf + s->len, buf, buflen);
        s->len += buflen;
    }

    p = s->buf;
    len = s->len;

    do {
        if(len) {
            type = (*p & 0xC0) >> 6;
            header_len = (*p & 0x30) >> 4;
            ts = (*p & 0xF);
        }

        if(type) {
            required = 2 + header_len;
        } else {
            required = 1 + header_len;
        }

        if(len < required) {
            break;
        }

        p++;

        s->last_data->next = malloc(sizeof(struct usb_data_s));
        s->last_data = s->last_data->next;
        memset(s->last_data, 0, sizeof(struct usb_data_s));

        /* Write TS that can be 1 2 3 4 bytes */
        for(i=0; i < header_len; i++)
            ts += (uint64_t)(*p++) << (i*8+4);

        s->ts += ts;
        s->last_data->ts = s->ts;
        s->last_data->type = type;
        if(type){
            s->last_data->val = *p++;
        }

        len -= required;
    } while(len);

    if(len) {
        tmp = malloc(len);
        memcpy(tmp, p, len);
        free(s->buf);
        s->buf = tmp;
        s->len = len;
    } else {
        s->len = 0;
        if(s->buf){
            free(s->buf);
        }
        s->buf = NULL;
    }

    decode_data(s);
}

void printhex(unsigned char *buf, int len)
{
    int i;
    for (i=0; i < len; i++)
        printf("%02x ", buf[i]);
    printf("\n");
}

void print_data(struct usb_session_s *s)
{
    struct usb_data_s *d = &s->data_list;

    while(d->next){
        d = d->next;
        switch(d->type){
            case USB_HEADER_TYPE_NONE:
                break;
            case USB_HEADER_TYPE_EVENT:
                printf("%ld:\tEvent: %02x\n", d->ts, d->val);
                break;
            case USB_HEADER_TYPE_DATA:
                break;
            case USB_HEADER_TYPE_RXCMD:
                printf("%ld:\tRxCMD: %02x\n", d->ts, d->val);
                printf("RXCMD: ID: %d EV_ENCODING: %d VBUS_STATE: %d DATA_STATE: %d\n",USB_RXCMD_ID(d->val), USB_RXCMD_EV_ENCODING(d->val), USB_RXCMD_VBUS_STATE(d->val), USB_RXCMD_DATA_STATE(d->val));
        }
    }
}

int usb_read_event(struct usb_session_s *s, uint8_t *event)
{
    int ret = 0;

    if(s->last_event != USB_EVENT_NONE) {
        *event = s->last_event;
        s->last_event = USB_EVENT_NONE;
        ret = 1;
    }

    return ret;
}

int usb_read_packet(struct usb_session_s *s, uint8_t *type, uint8_t *buf, uint32_t *len, uint64_t *ts)
{
    struct usb_packet_s *packet;

    packet = s->last_packet_read->next;

    if(packet){
        *type = packet->type;
        *len = packet->len;
        memcpy(buf, packet->buf, packet->len);
        *ts = packet->ts * 50 / 3;
        s->last_packet_read = packet;
        return 1;
    }
    return 0;
}

int usb_read_data(struct usb_session_s *s, uint8_t *type, uint8_t *val, uint64_t *ts)
{
    struct usb_data_s *data;

    data = s->last_data_read->next;
    while(data){
        if(data->type == 0){
            if(data->next){
                data = data->next;
                continue;
            } else {
                s->last_data_read = data;
                return 0;
            }
        }
        *type = data->type;
        *val = data->val;
        *ts = data->ts * 50 / 3;
        s->last_data_read = data;
        return 1;
    }
    return  0;
}

void usb_swap_bytes(uint8_t *dst, uint8_t *src, uint32_t len)
{
    int i;

    if(len % 2)
        printf("warning: odd swap bytes len\n");

    for (i=0; i<len; i+=2)
    {
        dst[i] = src[i+1];
        dst[i+1] = src[i];
    }
}

int usb_write_session(struct usb_session_s *s, FILE *out)
{
    int len = 0;
    struct usb_raw_s *raw;
    uint8_t *swp;

    raw = s->raw_list.next;
    while (raw) {
        // printf("write (%d) %p\n", raw->len, raw->buf);

        /* file stored in byte swapped format */

        swp = malloc(raw->len);
        usb_swap_bytes(swp, raw->buf, raw->len);

        // fwrite(raw->buf, 1, raw->len, out);
        fwrite(swp, 1, raw->len, out);
        len += raw->len;
        raw = raw->next;

        free(swp);
    }

    return len;
}

void usb_reset_timestamp(struct usb_session_s *s)
{
    s->ts = 0;
}

struct usb_session_s *usb_new_session()
{
    struct usb_session_s *sess;

    sess = malloc(sizeof(struct usb_session_s));
    memset(sess, 0, sizeof(struct usb_session_s));
    sess->last_data = &sess->data_list;
    sess->last_data_decoded = &sess->data_list;
    sess->last_data_read = &sess->data_list;
    sess->last_packet = &sess->packet_list;
    sess->last_packet_read = &sess->packet_list;
    sess->last_raw = &sess->raw_list;

    return sess;
}

void usb_free_session(struct usb_session_s *s)
{
    struct usb_raw_s *raw, *p_raw;
    struct usb_packet_s *pkt, *p_pkt;
    struct usb_data_s *data, *p_data;

    raw = s->raw_list.next;
    while (raw) {
        p_raw = raw;
        free(p_raw->buf);
        raw = p_raw->next;
        if(p_raw != &s->raw_list)
            free(p_raw);
    }

    pkt = s->packet_list.next;
    while(pkt){
        p_pkt = pkt;
        free(p_pkt->buf);
        pkt = p_pkt->next;
        if(p_pkt != &s->packet_list)
            free(p_pkt);
    }

    data = s->data_list.next;
    while(data){
        p_data = data;
        data = p_data->next;
        if(p_data != &s->data_list)
            free(p_data);
    }

    if (s->buf)
        free(s->buf);
    free(s);
}

/*
   int main()
   {
   struct usb_session_s *sess;
   FILE *in, *out;
   size_t len;
   uint32_t plen;
   uint8_t buf[MAX_CHUNK_SIZE];
   uint8_t swp[MAX_CHUNK_SIZE];
   uint8_t type;
   uint8_t val;
   uint64_t ts;

   sess = usb_new_session();

   in = fopen("../../Samples/hs_harddisk.usb", "rb");
   while(!feof(in)){
   len = fread(swp, 1, MAX_CHUNK_SIZE, in);
   if(len < 0)
   exit(0);

   usb_swap_bytes(buf, swp, len);

   usb_add_data(sess, buf, len);

   while(usb_read_data(sess, &type, &val, &ts)){
   printf("Data: %d %02x %ld\n", type, val, ts);
   }
   while(usb_read_packet(sess, &type, buf, &plen, &ts)){
   printf("got packet %ld %d %d: ", ts, type, plen);
   printhex(buf, plen);

   }
   }

   out = fopen("out.bin", "wb");
   usb_write_session(sess, out);

   usb_free_session(sess);
   }
*/
