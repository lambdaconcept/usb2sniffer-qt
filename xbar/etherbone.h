#ifndef __ETHERBONE_H_
#define __ETHERBONE_H_

int eb_make_read_pkt( uint32_t addr, uint32_t r_count, char **buf, size_t *len);
int eb_make_write_pkt( uint32_t addr, uint32_t *data, uint32_t w_count, char **buf, size_t *len);
int eb_decode_rcv_pkt(char *buf, int blen, uint32_t **data, size_t *len);

#endif
