#ifndef USBRECORD_H
#define USBRECORD_H

#include <QString>
#include <QVector>
#include <QVariant>
#include <QBrush>
#include <QFont>

#define RECORD_NAME     0
#define RECORD_TS       1
#define RECORD_DEVICE   2
#define RECORD_ENDPOINT 3
#define RECORD_STATUS   4
#define RECORD_LENGTH   5
#define RECORD_SUMMARY  6

class USBRecord
{
public:
    USBRecord();
    virtual ~USBRecord();

    static const QVector<QString> s_header;

    virtual QVariant data(int column) const = 0;
    virtual QBrush background() const;
    virtual QFont font(int column) const;
    virtual const QString asciiData();
    virtual const QString asciiPacket();
    virtual const QString details();
};

#endif // USBRECORD_H
