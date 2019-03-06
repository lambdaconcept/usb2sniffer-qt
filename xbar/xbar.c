#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include "etherbone.h"
#define CSR_ACCESSORS_DEFINED 1
#include "csr.h"
#include "sdram_phy.h"

struct xbar_s {
  uint32_t magic;
  uint32_t streamid;
  uint32_t len;
}__attribute__((packed));


int gfd;

void cdelay(int val)
{
  usleep(val);
}

int ubar_send_packet(int fd, char *buf, size_t len, int streamid)
{
  char *tosend;
  uint32_t *val;
  int i;

  tosend = malloc(len + 12);
  val = (uint32_t*)tosend;
  *(val++) = 0x5aa55aa5;// 0xa55aa55a;
  *(val++) =  streamid;
  *(val++) = len;
  memcpy(tosend+12, buf, len);

  /*  for(i = 0; i < len+12; i++){
    printf("%02x ", (unsigned char)tosend[i]);
  }
  printf("\n"); */
  write(fd, tosend, len+12);
  free(tosend);
  return 0;

}

size_t readft(int fd, void *buf, size_t len)
{
  size_t toread=len;
  char *pnt=(char*)buf;
  size_t rdl;

  while(toread){
    rdl = read(fd, pnt, toread);
    if (rdl < 0)
        exit(0);
    if(rdl > toread)
      exit(0);
    pnt += rdl;
    toread-=rdl;
  }
  return len;
}

int ubar_recv_packet(int fd, char **buf, size_t *len)
{
  struct xbar_s xbar;
  char *tmp;
  unsigned char header[4];

  memset(header,0, 4);
  do{
    header[3] = header[2];
    header[2] = header[1];
    header[1] = header[0];
    readft(fd, header, 1);
    //printf("header %02x %02x %02x %02x\n", header[0], header[1], header[2], header[3] );
  }while(memcmp(header, "\x5a\xa5\x5a\xa5", 4));
  xbar.magic = 0x5aa55aa5;
  readft(fd, (unsigned char*)&xbar + 4, 8);
  //printf("XBAR: %08x %08x %08x %d\n", xbar.magic, (unsigned)xbar.streamid, (unsigned )xbar.len, rdl);
  if(xbar.len > 32768)
    {
      exit(1);
    }
  tmp = malloc(xbar.len);

  readft(fd, tmp, xbar.len);

  *buf = tmp;
  *len = xbar.len;
  return xbar.streamid;
}

uint32_t  eb_read_reg32(int fd, uint32_t addr)
{
  char *buf;
  size_t len;
  uint32_t *data = NULL;
  size_t dlen;
  uint32_t ret = 0;
  int streamid;

  eb_make_read_pkt(addr, 1, &buf, &len);
  ubar_send_packet(fd, buf, len, 0);
  free(buf);
  do {
      streamid = ubar_recv_packet(fd, &buf, &len);
      printf("streamid %d\n", streamid);
      if (streamid && buf) {
          free(buf);
      }
  } while(streamid);
  eb_decode_rcv_pkt(buf, len, &data, &dlen);
  free(buf);
  if (data) {
    ret = data[0];
    free(data);
  }
  return ret;
}

void  eb_write_reg32(int fd, uint32_t addr, uint32_t val)
{
  char *buf;
  size_t len;
  uint32_t *data;
  size_t dlen;
  uint32_t ret;

  eb_make_write_pkt(addr, &val, 1, &buf, &len);
  ubar_send_packet(fd, buf, len, 0);
  free(buf);
}


void csr_writel(uint32_t value, uint32_t addr)
{
  eb_write_reg32(gfd, addr, value);
}

uint32_t csr_readl(uint32_t addr)
{
  return eb_read_reg32(gfd, addr);
}

uint8_t ulpi_read_reg(int fd, uint8_t addr)
{
  eb_write_reg32(fd, CSR_ULPI_CORE0_REG_ADR_ADDR, addr);
  eb_write_reg32(fd, CSR_ULPI_CORE0_REG_READ_ADDR, 1);
  while(!eb_read_reg32(fd, CSR_ULPI_CORE0_REG_DONE_ADDR));
  return eb_read_reg32(fd, CSR_ULPI_CORE0_REG_DAT_R_ADDR);
}

uint8_t ulpi_write_reg(int fd, uint8_t addr, uint8_t val)
{
  eb_write_reg32(fd, CSR_ULPI_CORE0_REG_ADR_ADDR, addr);
  eb_write_reg32(fd, CSR_ULPI_CORE0_REG_DAT_W_ADDR, val);
  eb_write_reg32(fd, CSR_ULPI_CORE0_REG_WRITE_ADDR, 1);
  while(!eb_read_reg32(fd, CSR_ULPI_CORE0_REG_DONE_ADDR));

}

void ulpi_reset(int fd, uint32_t val)
{
  eb_write_reg32(fd, CSR_ULPI_PHY0_ULPI_PHY_RESET_ADDR, val);
}

void ulpi_enable(int fd, uint32_t val)
{
  eb_write_reg32(fd, CSR_ULPI_CORE0_ENABLE_SOURCE_ADDR, val);
}

void ulpi_dump(int fd)
{
  int i;
  printf("Registers:");
  for(i=0; i< 0x19; i++)
    printf("Reg %02x -> %02x\n", i, ulpi_read_reg(fd, i));
  printf("\n");
}

void ulpi_init(int fd)
{
  ulpi_reset(fd, 0);
  usleep(100000);

  ulpi_dump(fd);
  ulpi_write_reg(fd, 0x04, 0x48);
  ulpi_write_reg(fd, 0x0a, 0x00);
  ulpi_write_reg(fd, 0x0f, 0x1f);
  ulpi_write_reg(fd, 0x12, 0x1f);
}
