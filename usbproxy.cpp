#include <iostream>

#include "usbproxy.h"
#include "usbitem.h"

USBProxy::USBProxy(QObject *parent)
    : QSortFilterProxyModel (parent)
{
    setRecursiveFilteringEnabled(true);
}

void USBProxy::setFilter(const QString &text)
{
    m_filter = text;
    invalidateFilter();
}

bool USBProxy::filterAcceptsRow(int sourceRow,
        const QModelIndex &sourceParent) const
{
    bool accept = false;

    /* Search inside record name */

    QModelIndex index = sourceModel()->index(sourceRow, RECORD_NAME, sourceParent);
    accept = sourceModel()->data(index).toString().contains(m_filter);
    if (accept)
        return accept;

    /* Search inside record status */

    /* Accept if parent transaction is selected */

    if (sourceParent.isValid()) {
        USBItem *item = static_cast<USBItem*>(sourceParent.internalPointer());
        accept = item->data(RECORD_STATUS).toString().contains(m_filter);
    }

    return accept;
}
