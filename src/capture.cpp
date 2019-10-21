#include <iostream>

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

extern ftdev_t gfd;

#ifdef __cplusplus
}
#endif

const QVector<QString> CaptureConfig::s_speedStr = {
    "High Speed",
    "Full Speed",
    "Low Speed"
};

QString CaptureConfig::speedStr()
{
    return s_speedStr.value(speed);
}

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
    ftdev_t fd;
    int ret;
    char *buf;
    char *pktbuf;
    int streamid;
    size_t len;
    uint32_t plen;
    uint8_t type;
    uint8_t val;
    uint64_t ts;
    uint8_t event;
    uint32_t drop_count;
    std::vector<std::tuple<uint64_t, uint8_t, uint8_t>> messageBuffer;

    bool stop_sent = false;
    bool stop_event = false;
    bool start_event = false;
    m_stoprequest = false;

    ret = ft60x_open(&fd, m_config->device.toUtf8().constData());
    if (ret < 0) {
        emit captureDeviceNotFound();
        return;
    }
    memcpy(&gfd, &fd, sizeof(ftdev_t));

    /* configure sdram */
    sdram_configure();

    /* flush fifo and cores */
    rst_manager_reset_write(1);

    /* ulpi switch */
    ulpi_sw_oe_n_out_write(0);
    ulpi_sw_s_out_write(0);

    /* ulpi init */
    ulpi_init(fd, m_config->speed);

    /* enable timer */
    iticore0_packer_time_enable_write(1);

    /* generate start pattern */
    iticore0_start_pattern_write(1);

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

            /* generate event stop */
            iticore0_packer_ev_event_write(USB_EVENT_STOP);
            iticore0_packer_ev_event_write(USB_EVENT_STOP);

            /* disable timer */
            iticore0_packer_time_enable_write(0);
        }

        streamid = ubar_recv_packet(fd, &buf, &len);
        if(streamid < 0) {
            emit captureDeviceDisconnected();
            goto exit;
        } else if (streamid == 1) {
            usb_add_data(m_sess, (uint8_t*)buf, len);

            while(usb_read_data(m_sess, &type, &val, &ts)) {
                if (start_event) {
                    messageBuffer.push_back(std::make_tuple(ts, type, val));
                }
            }

            while(usb_read_packet(m_sess, &type, (uint8_t*)pktbuf, &plen, &ts)) {
                if (start_event) {
                    m_model->addPacket(new USBPacket(ts, QByteArray(pktbuf, plen)));
                }
            }

            while(usb_read_event(m_sess, &event)) {
                switch(event) {
                case USB_EVENT_STOP:
                    stop_event = true;
                    break;
                case USB_EVENT_START:
                    start_event = true;
                    usb_reset_timestamp(m_sess);
                    break;
                default:
                    break;
                }
            }
        }

        if (messageBuffer.size() > 1000) {
            m_msg->addMessageVector(messageBuffer);
            messageBuffer.clear();
        }

        if (buf)
            free(buf);
    }

    /* Append last bufferized messages on capture stop */
    m_msg->addMessageVector(messageBuffer);

exit:
    m_model->lastPacket();

    free(pktbuf);
    ft60x_close(fd);
}
