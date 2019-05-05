#include "usbitem.h"
#include "usbpacket.h"
#include "usbmodel.h"
#include "usbproxy.h"

#include <iostream>

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
    std::cout << "handling row " << sourceRow << std::endl;

    QModelIndex index = sourceModel()->index(sourceRow, RECORD_NAME, sourceParent);

    if (!m_filter) {
        return true;
    }

    quint8 pid = usbModel()->getPid(index);

    /* Search inside record name */
    if (pid == PID_SOF) {
        return m_filter->sof;
    } else if (pid == PID_SPLIT) {
        return true; // XXX FIXME SPLIT filter not yet implemented
    }

    /* Search inside record status */

    /* Accept if parent transaction is selected */

    if (sourceParent.isValid()) {
        USBItem *item = static_cast<USBItem*>(sourceParent.internalPointer());
        QString status = item->data(RECORD_STATUS).toString();
        if (status.contains("NAK") || status.contains("Incomplete")) {
            if (item->data(RECORD_NAME).toString().contains("IN")) {
                return m_filter->nakIn;
            } else if (item->data(RECORD_NAME).toString().contains("OUT")) {
                return m_filter->nakOut;
            } else if (item->data(RECORD_NAME).toString().contains("SETUP")) {
                return m_filter->nakSetup;
            } else {
                return true;
            }
        } else {
            return true;
        }
    }

    return false;
}

USBModel* USBProxy::usbModel() const
{
    return static_cast<USBModel*>(sourceModel());
}
