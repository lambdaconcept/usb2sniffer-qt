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
    virtual const QString asciiData() = 0;
    virtual const QString asciiPacket() = 0;
    virtual const QString details() = 0;
};

#endif // USBRECORD_H
