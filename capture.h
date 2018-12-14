#ifndef CAPTURE_H
#define CAPTURE_H

#include <QThread>

#include "usbmodel.h"

class CaptureThread : public QThread
{
    Q_OBJECT

    void run();

signals:
    void resultReady(USBModel *usbModel);
};


#endif // CAPTURE_H
