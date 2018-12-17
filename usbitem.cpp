#include "usbitem.h"

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
    return USBRecord::s_header.count();
}

QVariant USBItem::headerData(int column) const
{
    return USBRecord::s_header.value(column);
}

USBItem *USBItem::parentItem()
{
    return m_parentItem;
}

QVariant USBItem::data(int column) const
{
    return m_record->data(column);
}

QBrush USBItem::background() const
{
    return m_record->background();
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
