#include <iostream>

#include "capture.h"
#include "usbaggregator.h"

#include <unistd.h>
#include <fcntl.h>

#define CSR_ACCESSORS_DEFINED 1

#ifdef __cplusplus
extern "C" {
#endif

#include "xbar/etherbone.h"
#include "xbar/csr.h"
#include "xbar/sdram_phy.h"
#include "xbar/xbar.h"

#ifdef __cplusplus
}
#endif

/*
void CaptureThread::run()
{
    USBAggregator aggregator;
    USBModel *usbModel = new USBModel(aggregator.getRoot());

    for (int i = 0; i < 5; ++i) {
        aggregator.append(new USBPacket(i, QByteArray::fromHex("a50f18")));

        sleep(1); // FIXME
    }
    aggregator.append(new USBPacket(10, QByteArray::fromHex("d2")));

    emit resultReady(usbModel);
}
*/

void CaptureThread::run()
{
    int fd;
    char *buf;
    size_t len;
    char *data;
    unsigned long long int timestamp;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    USBAggregator aggregator;
    USBModel *usbModel = new USBModel(aggregator.getRoot());

    fd = open("/dev/ft60x0", O_RDWR, mode);

    init_sequence();

    ulpi_reset(fd, 0);
    usleep(10000);

    ulpi_init(fd);

    std::cout << "init done\n";

    // while(1){
    for (int var = 0; var < 450; ++var)
    {
        if(ubar_recv_packet(fd, &buf, &len) == 1)
        {
            memcpy(&len, buf, sizeof(int));
            memcpy(&timestamp, buf + sizeof(int), 8);
            data = buf + 12;

            aggregator.append(new USBPacket(timestamp, QByteArray(data, len)));
        }
        usleep(100);
        free(buf);
    }

    close(fd);

    emit resultReady(usbModel);
}
