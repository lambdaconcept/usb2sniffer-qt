#ifndef __XBAR_H
#define __XBAR_H

#include <strings.h>
#include <stdint.h>

#include "ft60x/fops.h"

int ubar_recv_packet(ftdev_t fd, char **buf, size_t *len);
void ulpi_reset(ftdev_t fd, uint32_t val);
void ulpi_init(ftdev_t fd, int speed);
void ulpi_enable(ftdev_t fd, uint32_t val);

void cdelay(int val);

#endif
