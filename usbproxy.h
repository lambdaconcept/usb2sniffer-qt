#ifndef USBPROXY_H
#define USBPROXY_H

#include <QString>
#include <QSortFilterProxyModel>

class USBProxy : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    USBProxy(QObject *parent = 0);
    void setFilter(const QString &text);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

private:
    QString m_filter;
};

#endif // USBPROXY_H
