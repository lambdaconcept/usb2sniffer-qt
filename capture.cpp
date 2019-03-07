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
#include "parser/parse.h"

extern int gfd;

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

/*
void CaptureThread::run()
{
    for (int i = 0; i < 2; i++)
    {
        m_model->addPacket(new USBPacket(1, QByteArray::fromHex("a5da0f")));
        m_msg->addMessage(1, 2, 0xa5);
        m_msg->addMessage(1, 2, 0xda);
        m_msg->addMessage(1, 2, 0x0f);
        sleep(1);
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
*/

void CaptureThread::run()
{
    int fd;
    struct usb_session_s *sess;
    char *buf;
    char *pktbuf;
    size_t len;
    uint32_t plen;
    uint8_t type;
    uint8_t val;
    uint64_t ts;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    std::cout << "config: " << m_config->device.toStdString() << "\n";

    fd = open(m_config->device.toUtf8().constData(), O_RDWR, mode);
    if (fd < 0) {
        QMessageBox::warning(nullptr, "Error", "Capture device not found");

        return;
    }
    gfd = fd;

    /* configure sdram */
    sdram_configure();

    /* ulpi switch */
    ulpi_sw_oe_n_out_write(0);
    ulpi_sw_s_out_write(0);

    /* ulpi init 0 */
    ulpi_init(fd);

    /* Start capture */
    ulpi_enable(fd, 1);

    pktbuf = (char *)malloc(2048);
    sess = usb_new_session();

    while(1)
    // for (int var = 0; var < 450; ++var)  // XXX FIXME
    {
        if(ubar_recv_packet(fd, &buf, &len) == 1)
        {
            usb_add_data(sess, (uint8_t*)buf, len);
            while(usb_read_data(sess, &type, &val, &ts)){
                m_msg->addMessage(ts, type, val);
            }
            while(usb_read_packet(sess, &type, (uint8_t*)pktbuf, &plen, &ts)){
                // printf("add packet\n");
                m_model->addPacket(new USBPacket(ts, QByteArray(pktbuf, plen)));
            }
        }
        if (buf)
            free(buf);
    }
    m_model->lastPacket();

    free(pktbuf);
    close(fd);
}
