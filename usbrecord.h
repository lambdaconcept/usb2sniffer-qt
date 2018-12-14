#ifndef USBRECORD_H
#define USBRECORD_H

#include <QString>
#include <QVariant>

class USBRecord
{
public:
    USBRecord();
    virtual ~USBRecord();

    virtual QVariant data(int column) const = 0;
    virtual const QString asciiData();
    virtual const QString asciiPacket();
    virtual const QString details();
};

#endif // USBRECORD_H
