#ifndef __XBAR_H
#define __XBAR_H

#include <strings.h>
#include <stdint.h>

int ubar_recv_packet(int fd, char **buf, size_t *len);
void ulpi_reset(int fd, uint32_t val);
void ulpi_init(int fd);
void cdelay(int val);

#endif
