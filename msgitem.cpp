#include "msgitem.h"

MSGItem::MSGItem(MSGItem *parentItem)
{
    m_parentItem = parentItem;
}

MSGItem::~MSGItem()
{
    qDeleteAll(m_childItems);
}

void MSGItem::appendChild(MSGItem *item)
{
    m_childItems.append(item);
}

MSGItem *MSGItem::child(int row)
{
    return m_childItems.value(row);
}

int MSGItem::childCount() const
{
    return m_childItems.count();
}

int MSGItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<MSGItem*>(this));

    return 0;
}

int MSGItem::columnCount() const
{
    return 3; // XXX
}

QVariant MSGItem::headerData(int column) const
{
    return "TOTO"; // XXX
}

MSGItem *MSGItem::parentItem()
{
    return m_parentItem;
}

QVariant MSGItem::data(int column) const
{
    return "DATA"; // XXX
}
