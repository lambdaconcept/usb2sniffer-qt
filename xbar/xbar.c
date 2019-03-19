#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>

#include "ft60x/fops.h"
#include "etherbone.h"
#define CSR_ACCESSORS_DEFINED 1
#include "csr.h"
#include "sdram_phy.h"

struct xbar_s {
    uint32_t magic;
    uint32_t streamid;
    uint32_t len;
}__attribute__((packed));

ftdev_t gfd;

void cdelay(int val)
{
    usleep(val);
}

int ubar_send_packet(ftdev_t fd, char *buf, size_t len, int streamid)
{
    char *tosend;
    uint32_t *val;

    tosend = malloc(len + 12);
    val = (uint32_t*)tosend;
    *(val++) = 0x5aa55aa5;
    *(val++) =  streamid;
    *(val++) = len;
    memcpy(tosend+12, buf, len);

    /*  for(i = 0; i < len+12; i++){
        printf("%02x ", (unsigned char)tosend[i]);
        }
        printf("\n"); */
    ft60x_write(fd, tosend, len+12);
    free(tosend);
    return 0;
}

size_t readft(ftdev_t fd, void *buf, size_t len)
{
    size_t toread=len;
    char *pnt=(char*)buf;
    ssize_t rdl;

    while(toread){
        rdl = ft60x_read(fd, pnt, toread);
        if (rdl < 0) {
            printf("rdl: %ld\n", rdl);
            return 0;
        }
        if(rdl > toread) {
            printf("rdl: %ld\n", rdl);
            return 0;
        }
        pnt += rdl;
        toread-=rdl;
    }
    /*
       for (int i=0; i<len; i++) {
       printf("%02x ", ((unsigned char*)buf)[i]);
       }
       printf("\n");
       */
    return len;
}

int ubar_recv_packet(ftdev_t fd, char **buf, size_t *len)
{
    struct xbar_s xbar;
    char *tmp;
    uint32_t header;

    do {
        if(!readft(fd, &header, 4)) {
            return -1;
        }
        // printf("magic header: %08x\n", header);
    } while(header != 0x5aa55aa5);
    xbar.magic = 0x5aa55aa5;
    if (!readft(fd, (unsigned char*)&xbar + 4, 8)) {
        return -1;
    }
    // printf("XBAR: %08x %08x %08x\n", xbar.magic, (unsigned)xbar.streamid, (unsigned )xbar.len);
    if(xbar.len > 32768)
    {
        printf("xbar len: %d\n", xbar.len);
        return -1;
    }
    tmp = malloc(xbar.len);

    if (!readft(fd, tmp, xbar.len)) {
        free(tmp);
        return -1;
    }

    *buf = tmp;
    *len = xbar.len;
    return xbar.streamid;
}

uint32_t  eb_read_reg32(ftdev_t fd, uint32_t addr)
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
        if (streamid < 0) {
            printf("error recv xbar packet\n");
            return -1;
        }
        // printf("streamid %d\n", streamid);
        if ((streamid > 0) && buf) {
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

void  eb_write_reg32(ftdev_t fd, uint32_t addr, uint32_t val)
{
    char *buf;
    size_t len;

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

uint8_t ulpi_read_reg(ftdev_t fd, uint8_t addr)
{
    eb_write_reg32(fd, CSR_ULPI_CORE0_REG_ADR_ADDR, addr);
    eb_write_reg32(fd, CSR_ULPI_CORE0_REG_READ_ADDR, 1);
    while(!eb_read_reg32(fd, CSR_ULPI_CORE0_REG_DONE_ADDR));
    return eb_read_reg32(fd, CSR_ULPI_CORE0_REG_DAT_R_ADDR);
}

void ulpi_write_reg(ftdev_t fd, uint8_t addr, uint8_t val)
{
    eb_write_reg32(fd, CSR_ULPI_CORE0_REG_ADR_ADDR, addr);
    eb_write_reg32(fd, CSR_ULPI_CORE0_REG_DAT_W_ADDR, val);
    eb_write_reg32(fd, CSR_ULPI_CORE0_REG_WRITE_ADDR, 1);
    while(!eb_read_reg32(fd, CSR_ULPI_CORE0_REG_DONE_ADDR));
}

void ulpi_reset(ftdev_t fd, uint32_t val)
{
    eb_write_reg32(fd, CSR_ULPI_PHY0_ULPI_PHY_RESET_ADDR, val);
}

void ulpi_enable(ftdev_t fd, uint32_t val)
{
    eb_write_reg32(fd, CSR_ULPI_CORE0_ENABLE_SOURCE_ADDR, val);
}

void ulpi_dump(ftdev_t fd)
{
    int i;
    printf("Registers:");
    for(i=0; i< 0x19; i++)
        printf("Reg %02x -> %02x\n", i, ulpi_read_reg(fd, i));
    printf("\n");
}

void ulpi_init(ftdev_t fd, int speed)
{
    ulpi_reset(fd, 1);
    usleep(100000);

    ulpi_reset(fd, 0);
    usleep(100000);

    // ulpi_dump(fd);
    ulpi_write_reg(fd, 0x0a, 0x00); // disable 15kohms pull-down resistors
    ulpi_write_reg(fd, 0x0f, 0x1f); // clear interrupt rising
    ulpi_write_reg(fd, 0x12, 0x1f); // clear interrupt falling
    ulpi_write_reg(fd, 0x04, 0x48 | (speed & 3)); // set non driving and transceiver speed
}
