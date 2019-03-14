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

void CaptureThread::setUsbSession(struct usb_session_s *sess)
{
    m_sess = sess;
}

void CaptureThread::stop()
{
    m_stoprequest = true;
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
    char *buf;
    char *pktbuf;
    size_t len;
    uint32_t plen;
    uint8_t type;
    uint8_t val;
    uint64_t ts;
    uint8_t event;
    uint32_t drop_count;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    bool stop_sent = false;
    bool stop_event = false;
    m_stoprequest = false;

    fd = open(m_config->device.toUtf8().constData(), O_RDWR, mode);
    if (fd < 0) {
        QMessageBox::warning(nullptr, "Error", "Capture device not found");

        return;
    }
    gfd = fd;

    /* configure sdram */
    sdram_configure();

    /* flush fifo */
    // XXX FIXME

    /* ulpi switch */
    ulpi_sw_oe_n_out_write(0);
    ulpi_sw_s_out_write(0);

    /* ulpi init */
    ulpi_init(fd, m_config->speed);

    /* reset timer */
    itipacker0_time_reset_write(1);

    /* event start */
    itipacker0_ev_event_write(USB_EVENT_START);

    /* start capture */
    overflow0_reset_write(1);
    ulpi_enable(fd, 1);

    pktbuf = (char *)malloc(2048);

    while(!stop_event)
    {
        if (m_stoprequest && !stop_sent) {
            /* stop capture */
            ulpi_enable(fd, 0);
            stop_sent = true;

            drop_count = overflow0_count_read();
            printf("Stopped: packet dropped count (ulpi): %d\n", drop_count);

            /* event stop */
            itipacker0_ev_event_write(USB_EVENT_STOP);
            itipacker0_ev_event_write(USB_EVENT_STOP);
        }

        if(ubar_recv_packet(fd, &buf, &len) == 1)
        {
            /*
            printf("ubar_recv: %d\n", len);
            for (int i=0; i<len; i++) {
                printf("%02x ", buf[i]);
            }
            printf("\n");
            */
            usb_add_data(m_sess, (uint8_t*)buf, len);
            while(usb_read_data(m_sess, &type, &val, &ts)){
                // printf("add message\n");
                m_msg->addMessage(ts, type, val);
            }
            while(usb_read_packet(m_sess, &type, (uint8_t*)pktbuf, &plen, &ts)){
                // printf("add packet\n");
                m_model->addPacket(new USBPacket(ts, QByteArray(pktbuf, plen)));
            }
            while(usb_read_event(m_sess, &event)) {
                if (event == USB_EVENT_STOP) {
                    stop_event = true;
                }
            }
        }
        if (buf)
            free(buf);
    }
    m_model->lastPacket();

    free(pktbuf);
    close(fd);
}
