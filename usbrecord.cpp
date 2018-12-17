#include "usbrecord.h"

const QVector<QString> USBRecord::s_header = {
    "Record",
    "Timestamp",
    "Device",
    "Endpoint",
    "Status",
    "Length",
    "Summary",
};

USBRecord::USBRecord()
{

}

USBRecord::~USBRecord()
{

}

const QString USBRecord::asciiData()
{
    return QString();
}

const QString USBRecord::asciiPacket()
{
    return QString();
}

const QString USBRecord::details()
{
    return QString();
}
