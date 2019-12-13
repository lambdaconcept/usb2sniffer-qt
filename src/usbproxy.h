#ifndef USBPROXY_H
#define USBPROXY_H

#include <QString>
#include <QSortFilterProxyModel>
#include "usbproxyfilter.h"
#include "usbmodel.h"

class USBProxy : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    USBProxy(QObject *parent = 0);
    void setFilter(const USBProxyFilter *filter);

    /* search */
    QModelIndex nextSearch(const QByteArray &search);
    QModelIndex prevSearch(const QByteArray &search);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
    QModelIndex runSearch(const QByteArray &search);

private:
    const USBProxyFilter *m_filter = nullptr;
    QByteArray m_lastSearch;
    QList<QModelIndex> m_searchList;
    QList<QModelIndex>::const_iterator m_searchIt;
};

#endif // USBPROXY_H
