#include "msgitem.h"
#include "helpers.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "parser/parse.h"

#ifdef __cplusplus
}
#endif

const QVector<QString> MSGItem::s_header = {
    "Timestamp",
    "Type",
    "Value",
    "Details",
};

MSGItem::MSGItem(uint64_t ts, uint8_t type, uint8_t val, MSGItem *parentItem)
{
    m_parentItem = parentItem;

    m_ts = ts;
    m_type = type;
    m_val = val;
}

MSGItem::~MSGItem()
{
    m_mutex.lock();
    qDeleteAll(m_childItems);
    m_mutex.unlock();
}

void MSGItem::appendChild(MSGItem *item)
{
    m_mutex.lock();
    m_childItems.append(item);
    m_mutex.unlock();
}

MSGItem *MSGItem::child(int row)
{
    MSGItem *tmp;

    m_mutex.lock();
    tmp = m_childItems.value(row);
    m_mutex.unlock();

    return tmp;
}

int MSGItem::childCount()
{
    int count;

    m_mutex.lock();
    count = m_childItems.count();
    m_mutex.unlock();

    return count;
}

int MSGItem::row()
{
    int idx = 0;

    if (m_parentItem) {
        m_mutex.lock();
        idx = m_parentItem->m_childItems.indexOf(const_cast<MSGItem*>(this));
        m_mutex.unlock();
    }

    return idx;
}

int MSGItem::columnCount() const
{
    return s_header.count();
}

QVariant MSGItem::headerData(int column) const
{
    return s_header.value(column);
}

MSGItem *MSGItem::parentItem()
{
    return m_parentItem;
}

QVariant MSGItem::data(int column) const
{
    char *type;

    switch(column)
    {
        case MSG_TS:
            return formatTimestamp(m_ts);
        case MSG_TYPE:
            type = usb_get_header_type(m_type);
            if (type)
                return QString(type);
            else
                return QString("");
        case MSG_VALUE:
            return QString("%1").arg(m_val, 2, 16, QChar('0'));
        case MSG_DETAILS:
            return ""; // XXX to be implemented
        default:
            return QVariant();
    }
}
