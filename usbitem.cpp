#include "usbitem.h"

USBItem::USBItem(const quint64 timestamp,
                 const quint8 pid,
                 const quint8 dev,
                 const quint8 endpoint,
                 const quint16 crc,
                 const quint16 frameNumber,
                 const quint32 dataLen,
                 const QByteArray &data,

                 USBItem *parentItem)
{
    m_parentItem = parentItem;

    m_Timestamp = timestamp;
    m_Pid = pid;
    m_Dev = dev;
    m_Endpoint = endpoint;
    m_CRC = crc;
    m_FrameNumber = frameNumber;
    m_DataLen = dataLen;
    m_Data = data;
}

USBItem::~USBItem()
{
    qDeleteAll(m_childItems);
}

void USBItem::appendChild(USBItem *item)
{
    m_childItems.append(item);
}

USBItem *USBItem::child(int row)
{
    return m_childItems.value(row);
}

int USBItem::childCount() const
{
    return m_childItems.count();
}

int USBItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<USBItem*>(this));

    return 0;
}

int USBItem::columnCount() const
{
    return 8; // FIXME
}

QVariant USBItem::data(int column) const
{
    if (column < 8) { // FIXME
        if (column == 0) { // FIXME
            return m_Timestamp;
        }
        else if (column == 1) {
            return m_Pid;
        }
        else if (column == 2) {
            return m_Dev;
        }
        else if (column == 3) {
            return m_Endpoint;
        }
        else if (column == 4) {
            return m_CRC;
        }
        else if (column == 5) {
            return m_FrameNumber;
        }
        else if (column == 6) {
            return m_DataLen;
        }
        else if (column == 7) {
            return m_Data.toHex();
        }
    }

    return QVariant();
}

USBItem *USBItem::parentItem()
{
    return m_parentItem;
}
