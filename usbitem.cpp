#include "usbitem.h"

const QVector<QString> USBItem::s_header = {
    "Record",
    "Timestamp",
    "Device",
    "Endpoint",
    "Length",
    "Summary",
    // Status
    // Error
};

USBItem::USBItem(USBPacket *packet, USBItem *parentItem)
{
    m_parentItem = parentItem;
    m_packet = packet;
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
    return s_header.count();
}

QVariant USBItem::data(int column) const
{
    switch(column)
    {
        case 0:
            return m_packet->getPidStr();
        case 1:
            return m_packet->m_Timestamp;
        case 2:
            return QString("%1").arg(m_packet->m_Dev, 2, 16, QChar('0'));
        case 3:
            return QString("%1").arg(m_packet->m_Endpoint, 2, 16, QChar('0'));
        case 4:
            return m_packet->m_Data.count();
        case 5:
            return m_packet->m_Data.toHex();
        default:
            return QVariant();
    }
}

QVariant USBItem::headerData(int column) const
{
    return s_header.value(column);
}

USBItem *USBItem::parentItem()
{
    return m_parentItem;
}

const QString USBItem::asciiData()
{
    return m_packet->m_Data.toHex();

    // m_packet->m_Data.data(), m_packet->m_DataLen
}
