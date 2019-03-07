#ifndef CAPTURE_H
#define CAPTURE_H

#include <QThread>

#include "usbmodel.h"
#include "msgmodel.h"

namespace CaptureMask {
enum CaptureMask {
    RESERVED = 0x0001,
    OUT      = 0x0002,
    ACK      = 0x0004,
    DATA0    = 0x0008,
    PING     = 0x0010,
    SOF      = 0x0020,
    NYET     = 0x0040,
    DATA2    = 0x0080,
    SPLIT    = 0x0100,
    IN       = 0x0200,
    NAK      = 0x0400,
    DATA1    = 0x0800,
    PRE_ERR  = 0x1000,
    SETUP    = 0x2000,
    STALL    = 0x4000,
    MDATA    = 0x8000
    };
}

class CaptureConfig
{
public:
    QString device;
    int32_t rx_cmd = 0;
    int32_t pid_mask = 0;
};

class CaptureThread : public QThread
{
    Q_OBJECT

    void run();

public:
    void setConfig(CaptureConfig* config);
    void setModel(USBModel *model, MSGModel *msg);

private:
    CaptureConfig *m_config;
    USBModel *m_model;
    MSGModel *m_msg;
};

#endif // CAPTURE_H
