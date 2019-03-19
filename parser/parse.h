#ifndef __PARSE_H
#define __PARSE_H

#include <stdio.h>
#include <stdint.h>

#define MAX_CHUNK_SIZE  512

#define USB_HEADER_TYPE_NONE  0
#define USB_HEADER_TYPE_EVENT 1
#define USB_HEADER_TYPE_DATA  2
#define USB_HEADER_TYPE_RXCMD 3

#define USB_EVENT_NONE      0x00
#define USB_EVENT_START     0xe0
#define USB_EVENT_STOP      0xf1

#define USB_RXCMD_ID_MASK           0x40
#define USB_RXCMD_ID_SHIFT          6
#define USB_RXCMD_ID(x) ((x & USB_RXCMD_ID_MASK) >> USB_RXCMD_ID_SHIFT)
#define USB_RXCMD_EV_ENCODING_MASK  0x30
#define USB_RXCMD_EV_ENCODING_SHIFT 4
#define USB_RXCMD_EV_ENCODING(x) ((x & USB_RXCMD_EV_ENCODING_MASK) >> USB_RXCMD_EV_ENCODING_SHIFT)
#define USB_RXCMD_VBUS_STATE_MASK   0x0C
#define USB_RXCMD_VBUS_STATE_SHIFT  2
#define USB_RXCMD_VBUS_STATE(x) ((x & USB_RXCMD_VBUS_STATE_MASK) >> USB_RXCMD_VBUS_STATE_SHIFT)
#define USB_RXCMD_DATA_STATE_MASK   0x03
#define USB_RXCMD_DATA_STATE_SHIFT  0
#define USB_RXCMD_DATA_STATE(x) ((x & USB_RXCMD_DATA_STATE_MASK) >> USB_RXCMD_DATA_STATE_SHIFT)

#define USB_RXCMD_EV_ENCODING_RXACTIVE       1
#define USB_RXCMD_EV_ENCODING_RXERROR        2
#define USB_RXCMD_EV_ENCODING_HOSTDISCONNECT 4

#define USB_RXCMD_VBUS_STATE_SESSEND  0
#define USB_RXCMD_VBUS_STATE_VBUS     1
#define USB_RXCMD_VBUS_STATE_SESS_VLD 2
#define USB_RXCMD_VBUS_STATE_VBUS_VLD 3

struct usb_session_s;

void usb_add_data(struct usb_session_s *s, uint8_t *buf, uint32_t buflen);
int usb_read_event(struct usb_session_s *s, uint8_t *event);
int usb_read_packet(struct usb_session_s *s, uint8_t *type, uint8_t *buf, uint32_t *len, uint64_t *ts);
int usb_read_data(struct usb_session_s *s, uint8_t *type, uint8_t *val, uint64_t *ts);
struct usb_session_s *usb_new_session();
void usb_free_session(struct usb_session_s *s);
int usb_write_session(struct usb_session_s *s, FILE *out);
void usb_swap_bytes(uint8_t *dst, uint8_t *src, uint32_t len);
void usb_reset_timestamp(struct usb_session_s *s);

char *usb_get_header_type(int type);

#endif
