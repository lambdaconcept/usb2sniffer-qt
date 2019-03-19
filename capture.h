#ifndef CAPTURE_H
#define CAPTURE_H

#include <QThread>

#include "usbmodel.h"
#include "msgmodel.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "parser/parse.h"

#ifdef __cplusplus
}
#endif

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

namespace CaptureSpeed {
/* From ULPI XcvrSelect specification:
00b: Enables HS transceiver
01b: Enables FS transceiver
10b: Enables LS transceiver
11b: Enables FS transceiver for LS packets
*/
enum CaptureSpeed {
    HS = 0,
    FS = 1,
    LS = 2,
};
}

class CaptureConfig
{
public:
    QString device;
    int speed = 0;

    static const QVector<QString> s_speedStr;

    QString speedStr();
};

class CaptureThread : public QThread
{
    Q_OBJECT

    void run();

public:
    void setConfig(CaptureConfig* config);
    void setModel(USBModel *model, MSGModel *msg);
    void setUsbSession(struct usb_session_s *sess);
    void stop();

private:
    CaptureConfig *m_config;
    USBModel *m_model;
    MSGModel *m_msg;

    struct usb_session_s *m_sess;

    bool m_stoprequest;
};

#endif // CAPTURE_H
