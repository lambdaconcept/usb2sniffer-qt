#ifndef __PARSE_H
#define __PARSE_H

#include <stdint.h>

struct usb_session_s;

void usb_add_data(struct usb_session_s *s, uint8_t *buf, uint32_t buflen);
int usb_read_packet(struct usb_session_s *s, uint8_t *type, uint8_t *buf, uint32_t *len, uint64_t *ts);
int usb_read_data(struct usb_session_s *s, uint8_t *type, uint8_t *val, uint64_t *ts);
struct usb_session_s *usb_new_session();

char *usb_get_header_type(int type);

#endif
