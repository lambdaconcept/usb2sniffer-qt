#include <iostream>

#include <QMessageBox>

#include "capture.h"

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

void CaptureThread::setConfig(CaptureConfig* config)
{
    m_config = config;
}

void CaptureThread::setModel(USBModel *model, MSGModel *msg)
{
    m_model = model;
    m_msg = msg;
}

void CaptureThread::run()
{
    for (int i = 0; i < 2; i++)
    {
        m_model->addPacket(new USBPacket(1, QByteArray::fromHex("a5da0f")));
        m_msg->addMessage(1, 2, 0xa5);
        m_msg->addMessage(1, 2, 0xda);
        m_msg->addMessage(1, 2, 0x0f);
        sleep(1);
        printf("done sleep\n");
    }

    m_model->addPacket(new USBPacket(1, QByteArray::fromHex("2d01e8")));
    m_msg->addMessage(1, 2, 0x2d);
    m_msg->addMessage(1, 2, 0x01);
    m_msg->addMessage(1, 2, 0xe8);
    sleep(1);

    for (int i = 0; i < 3; i++)
    {
        m_model->addPacket(new USBPacket(1, QByteArray::fromHex("a5da0f")));
        sleep(1);
    }

    m_model->lastPacket();

    // emit resultReady(m_aggregator);
}
/*
void CaptureThread::run()
{
    int fd;
    char *buf;
    size_t len;
    char *data;
    unsigned long long int timestamp;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    std::cout << "config: " << m_config->device.toStdString() << "\n";

    USBAggregator *aggregator = new USBAggregator();

    fd = open(m_config->device.toUtf8().constData(), O_RDWR, mode);
    if (fd < 0) {
        QMessageBox::warning(nullptr, "Error", "Capture device not found");

        goto err;
    }

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

            aggregator->append(new USBPacket(timestamp, QByteArray(data, len)));
        }
        usleep(100);
        free(buf);
    }
    aggregator->done();

    close(fd);

err:
    emit resultReady(aggregator);
}
*/
