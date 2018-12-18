#ifndef CAPTURE_H
#define CAPTURE_H

#include <QThread>

#include "usbmodel.h"

class CaptureConfig
{
public:
    QString device;
    int32_t rx_cmd;
    int32_t pid_mask;
};

class CaptureThread : public QThread
{
    Q_OBJECT

    void run();

public:
    void setConfig(CaptureConfig* config);

private:
    CaptureConfig *m_config;

signals:
    void resultReady(USBModel *usbModel);
};

#endif // CAPTURE_H
