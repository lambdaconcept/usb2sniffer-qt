#ifndef USBITEM_H
#define USBITEM_H

#include <QList>
#include <QString>
#include <QVector>
#include <QByteArray>

#include "usbpacket.h"

class USBItem
{
public:
    explicit USBItem(USBPacket* packet, USBItem *parentItem = nullptr);
    ~USBItem();

    void appendChild(USBItem *child);

    USBItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    QVariant headerData(int column) const;
    int row() const;
    USBItem *parentItem();
    const QString asciiData();

    static const QVector<QString> s_header;

private:
    QList<USBItem*> m_childItems;
    USBItem *m_parentItem;
    USBPacket *m_packet;
};

#endif // USBITEM_H
