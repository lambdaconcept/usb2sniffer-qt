#ifndef USBPROXY_H
#define USBPROXY_H

#include <QString>
#include <QSortFilterProxyModel>

class USBProxyFilter
{
public:
    bool sof = true;
    /* For now Incomplete is treated as NAK */
    bool nakIn = true;
    bool nakOut = true;
    bool nakSetup = true;
    QString device;
    QString endpoint;
};

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
