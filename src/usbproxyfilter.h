#ifndef USBPROXYFILTER_H
#define USBPROXYFILTER_H

#include <QString>

struct USBProxyFilter
{
    bool sof = false;
    bool split = false;

    /* For now Incomplete is treated as NAK */
    bool nakIn = false;
    bool nakOut = false;
    bool nakSetup = false;
    bool nakPing = false;

    QString device;
    int deviceNum = -1;
    QString endpoint;
    int endpointNum = -1;
};

#endif // USBPROXYFILTER_H
