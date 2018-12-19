#include "usbproxy.h"
#include "usbitem.h"

USBProxy::USBProxy(QObject *parent)
    : QSortFilterProxyModel (parent)
{
    setRecursiveFilteringEnabled(true);
}

void USBProxy::setFilter(const USBProxyFilter *filter)
{
    m_filter = filter;
    invalidateFilter();
}

bool USBProxy::filterAcceptsRow(int sourceRow,
        const QModelIndex &sourceParent) const
{
    if (!m_filter) {
        return true;
    }

    /* Search inside record name */

    QModelIndex index = sourceModel()->index(sourceRow, RECORD_NAME, sourceParent);
    if (sourceModel()->data(index).toString().contains("SOF")) { // FIXME check pid type instead of string matching
        return m_filter->sof;
    }

    /* Search inside record status */

    /* Accept if parent transaction is selected */

    if (sourceParent.isValid()) {
        USBItem *item = static_cast<USBItem*>(sourceParent.internalPointer());
        if (item->data(RECORD_STATUS).toString().contains("NAK")) {
            if (item->data(RECORD_NAME).toString().contains("IN")) {
                return m_filter->nakIn;
            } else if (item->data(RECORD_NAME).toString().contains("OUT")) {
                return m_filter->nakOut;
            } else if (item->data(RECORD_NAME).toString().contains("SETUP")) {
                return m_filter->nakSetup;
            }
        } else {
            return true;
        }
    }

    return false;
}
