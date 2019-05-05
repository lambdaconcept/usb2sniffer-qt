#include "usbitem.h"

USBItem::USBItem(USBRecord *record, USBItem *parentItem)
{
    m_parentItem = parentItem;
    m_record = record;
}

USBItem::~USBItem()
{
    m_mutex.lock();
    qDeleteAll(m_childItems);
    m_mutex.unlock();
}

void USBItem::appendChild(USBItem *item)
{
    m_mutex.lock();
    m_childItems.append(item);
    m_mutex.unlock();
}

USBItem *USBItem::child(int row)
{
    USBItem *tmp;

    m_mutex.lock();
    tmp = m_childItems.value(row);
    m_mutex.unlock();

    return tmp;
}

int USBItem::childCount()
{
    int count;

    m_mutex.lock();
    count = m_childItems.count();
    m_mutex.unlock();

    return count;
}

int USBItem::row()
{
    int idx = 0;

    if (m_parentItem) {
        m_mutex.lock();
        idx = m_parentItem->m_childItems.indexOf(const_cast<USBItem*>(this));
        m_mutex.unlock();
    }

    return idx;
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

QFont USBItem::font(int column) const
{
    return m_record->font(column);
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

quint8 USBItem::getPid() const
{
    return m_record->getPid();
}
