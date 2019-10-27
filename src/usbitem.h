#ifndef USBITEM_H
#define USBITEM_H

#include <QList>
#include <QString>
#include <QVector>
#include <QBrush>
#include <QFont>
#include <QMutex>

#include "usbproxyfilter.h"
#include "usbrecord.h"

class USBItem
{
public:
    explicit USBItem(USBRecord* record, USBItem *parentItem = nullptr);
    ~USBItem();

    void appendChild(USBItem *child);
    USBItem *child(int row);
    int childCount();
    int columnCount() const;
    QVariant headerData(int column) const;
    int row();
    USBItem *parentItem();

    QVariant data(int column) const;
    QBrush background() const;
    QFont font(int column) const;
    const QString asciiData();
    const QString asciiPacket();
    const QString details();
    quint8 getPid() const;
    QPair<QByteArray, QByteArray> recordData();
    bool matchForFilter(const USBProxyFilter *filter) const;

private:
    QList<USBItem*> m_childItems;
    USBItem *m_parentItem;
    USBRecord *m_record;
    QMutex m_mutex;
};

#endif // USBITEM_H
