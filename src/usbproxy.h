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

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

private:
    const USBProxyFilter *m_filter = nullptr;
};

#endif // USBPROXY_H
