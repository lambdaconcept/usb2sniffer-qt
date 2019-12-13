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

    /* refresh search results when the display filter has changed */
    runSearch(m_lastSearch);
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

QModelIndex USBProxy::runSearch(const QByteArray &search)
{
    USBModel *source = static_cast<USBModel*>(sourceModel());
    if (!source) {
        return QModelIndex();
    }

    /* Reset last search */
    m_searchList.clear();
    m_lastSearch = search;
    if (search.isEmpty()) {
        return QModelIndex();
    }

    /* Run the search on the source model data */
    QList<QModelIndex> sourceList;
    source->runSearch(search, &sourceList);
    if (sourceList.isEmpty()) {
        return QModelIndex();
    }

    /* Filter the source list based on proxy filter visibility */
    QList<QModelIndex>::const_iterator it;
    for (it=sourceList.constBegin(); it!=sourceList.constEnd(); it++) {
        QModelIndex index = mapFromSource(*it);
        if (index.isValid()) {
            m_searchList.append(index);
        }
    }

    m_searchIt = m_searchList.constBegin();
    return *m_searchIt;
}

QModelIndex USBProxy::nextSearch(const QByteArray &search)
{
    if (search != m_lastSearch) {
        return runSearch(search);
    }

    if (m_searchList.isEmpty()) {
        return QModelIndex();
    }

    /* Go back to the beginning when reaching the end */
    m_searchIt++;
    if (m_searchIt != m_searchList.constEnd()) {
        return *m_searchIt;
    } else {
        m_searchIt = m_searchList.constBegin();
        return *m_searchIt;
    }
}

QModelIndex USBProxy::prevSearch(const QByteArray &search)
{
    if (search != m_lastSearch) {
        return runSearch(search);
    }

    if (m_searchList.isEmpty()) {
        return QModelIndex();
    }

    /* Restart from the end when the top is reached */
    if (m_searchIt != m_searchList.constBegin()) {
        m_searchIt--;
        return *m_searchIt;
    } else {
        m_searchIt = m_searchList.constEnd() - 1;
        return *m_searchIt;
    }
}
