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

USBItem::USBItem(USBRecord *record, USBItem *parentItem)
{
    m_parentItem = parentItem;
    m_record = record;
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

QVariant USBItem::headerData(int column) const
{
    return s_header.value(column);
}

USBItem *USBItem::parentItem()
{
    return m_parentItem;
}

QVariant USBItem::data(int column) const
{
    return m_record->data(column);
}

const QString USBItem::asciiData()
{
    return m_record->asciiData();
}

const QString USBItem::asciiPacket()
{
    return m_record->asciiPacket();
}

const QString USBItem::details()
{
    return m_record->details();
}
