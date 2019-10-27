#include "usbitem.h"
#include "usbpacket.h"
#include "usbmodel.h"
#include "usbproxy.h"

USBProxy::USBProxy(QObject *parent)
    : QSortFilterProxyModel (parent)
{
    setRecursiveFilteringEnabled(true);
}

void USBProxy::setFilter(const USBProxyFilter *filter)
{
    m_filter = filter;
    invalidate();
}

bool USBProxy::filterAcceptsRow(int sourceRow,
        const QModelIndex &sourceParent) const
{
    if (!m_filter) {
        return true;
    } else if (sourceParent.isValid()) {
        USBItem *item = static_cast<USBItem*>(sourceParent.internalPointer());
        return item->matchForFilter(m_filter);
    } else {
        return false;
    }
}
