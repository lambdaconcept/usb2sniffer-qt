#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

struct eb_header_s {
    uint16_t magic;             /* Magic 0x4E6F*/
    uint8_t pf:1;               /* Probe-Flag */
    uint8_t pr:1;               /* Probe-Response */
    uint8_t nr:1;               /* No-Read */
    uint8_t nc1:1;
    uint8_t version:4;          /* Version 1 */
    uint8_t port_size:4;        /* 8 x val */
    uint8_t addr_size:4;        /* 8 x Val */
    uint32_t pad1;

    uint8_t nc2:1;
    uint8_t wff:1;              /* If should be written to a FIFO register, the WF flag is set */
    uint8_t wca:1;              /* If config address space, the WCA flag is set */
    uint8_t cyc:1;              /* If last of a cycle, the CYC flag is set */
    uint8_t nc3:1;
    uint8_t rff:1;              /* Read Fifo */
    uint8_t rca:1;              /* Read Config Addr */
    uint8_t bca:1;              /* BaseRetAddr */
    uint8_t byte_enable;        /* Byte enable 8/16/32 */
    uint8_t w_count;            /* write count */
    uint8_t r_count;            /* read count */
}__attribute__((packed));

uint32_t wswap(uint32_t const val)
{
    uint8_t data[4];
    memcpy(&data, &val, sizeof(data));

    return ((uint32_t) data[3] << 0)
        | ((uint32_t) data[2] << 8)
        | ((uint32_t) data[1] << 16)
        | ((uint32_t) data[0] << 24);
}

void print_header(struct eb_header_s *h)
{
    printf("Magic: %04x\n", h->magic);
    printf("Version: %d\n", h->version);
    printf("NR: %d\n", h->nr);
    printf("PR: %d\n", h->pr);
    printf("PF: %d\n", h->pf);
    printf("Port Size: %d\n", h->port_size);
    printf("Adr Size: %d\n", h->addr_size);
    printf("CYC: %d\n", h->cyc);
    printf("BCA: %d\n", h->bca);
    printf("RCA: %d\n", h->rca);
    printf("Byte Enable: %01x\n", h->byte_enable);
    printf("Read cnt: %d\n", h->r_count);
    printf("Write cnt: %d\n", h->w_count);
}

void print_eb_packet(char *buf, int len)
{
    struct eb_header_s *h;
    uint32_t *val;
    int i;

    if(len < 12)
        return;
    h = (struct eb_header_s*)buf;
    //print_header(h);
    val = (uint32_t*)(buf +sizeof(struct eb_header_s));
    if(h->r_count){
        printf("Base addr: %08x\n", wswap( *(val++)));
        for(i = 0; i<h->r_count;i++){
            printf("Addr: %08x\n", wswap(*(val++)));
        }
    }
    if(h->w_count){
        printf("Base addr: %08x\n", wswap(*(val++)));
        for(i = 0; i<h->w_count;i++){
            printf("Value: %08x\n", wswap(*(val++)));
        }
    }
}

int eb_make_read_pkt( uint32_t addr, uint32_t r_count, char **buf, size_t *len)
{
    struct eb_header_s *ebh;
    char *tosend;
    int *val;
    int i;
    tosend = malloc(sizeof(struct eb_header_s) + 4 * (r_count + 1));
    memset(tosend, 0, sizeof(struct eb_header_s) + 4 * (r_count + 1));
    ebh=(struct eb_header_s*)tosend;
    ebh->magic = 0x6f4e;
    ebh->version = 1;
    ebh->port_size = 4;
    ebh->addr_size = 4;
    ebh->r_count = r_count;
    ebh->byte_enable = 0xf;
    val =  (uint32_t*)(tosend +sizeof(struct eb_header_s)+4);
    for(i=0; i < r_count; i++)
        *(val++) = wswap(addr + (i*4));
    *buf = tosend;
    *len = sizeof(struct eb_header_s) + 4 * (r_count + 1);
    return 0;
}

int eb_make_write_pkt( uint32_t addr, uint32_t *data, uint32_t w_count, char **buf, size_t *len)
{
    struct eb_header_s *ebh;
    char *tosend;
    uint32_t *val;
    int i;
    tosend = malloc(sizeof(struct eb_header_s) + 4 * (w_count + 1));
    memset(tosend, 0, sizeof(struct eb_header_s) + 4 * (w_count + 1));
    ebh=(struct eb_header_s*)tosend;
    ebh->magic = 0x6f4e;
    ebh->version = 1;
    ebh->port_size = 4;
    ebh->addr_size = 4;
    ebh->w_count = w_count;
    ebh->byte_enable = 0xf;
    val =  (uint32_t*)(tosend +sizeof(struct eb_header_s));
    *(val++) = wswap(addr);
    for(i=0; i < w_count; i++)
        val[i] = wswap(data[i]);
    *buf = tosend;
    *len = sizeof(struct eb_header_s) + 4 * (w_count + 1);
    return 0;
}

int eb_decode_rcv_pkt(char *buf, int blen, uint32_t **data, size_t *len)
{
    struct eb_header_s *h;
    uint32_t *val;
    int i;
    uint32_t *tmp;

    if(blen < 12)
        return -1;
    h = (struct eb_header_s*)buf;
    //print_header(h);
    val = (uint32_t*)(buf +sizeof(struct eb_header_s) + 4);
    tmp = malloc(h->w_count * sizeof(uint32_t));
    for(i=0; i < h->w_count; i++) {
        tmp[i] = wswap(val[i]);
    }
    *data = tmp;
    *len = h->w_count;
    return 0;
}
