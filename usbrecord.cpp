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

QBrush USBRecord::background() const
{
    return QBrush();
}

QFont USBRecord::font(int column) const
{
    return QFont();
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

QPair<QByteArray, QByteArray> USBRecord::recordData()
{
    return qMakePair(emptyByteArray, emptyByteArray);
}
