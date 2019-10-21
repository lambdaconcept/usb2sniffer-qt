#ifndef USBPROXYFILTER_H
#define USBPROXYFILTER_H

#include <QString>

struct USBProxyFilter
{
    bool sof = true;
    /* For now Incomplete is treated as NAK */
    bool nakIn = true;
    bool nakOut = true;
    bool nakSetup = true;
    bool nakPing = true;
    QString device;
    int deviceNum = -1;
    QString endpoint;
    int endpointNum = -1;
};

#endif // USBPROXYFILTER_H
