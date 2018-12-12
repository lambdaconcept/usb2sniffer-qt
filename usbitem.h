#ifndef USBITEM_H
#define USBITEM_H

#include <QList>
#include <QVector>
#include <QByteArray>

class USBItem
{
public:
    explicit USBItem(
            const quint64 timestamp,
            const quint8 pid,
            const quint8 dev,
            const quint8 endpoint,
            const quint16 crc,
            const quint16 frameNumber,
            const quint32 dataLen,
            const QByteArray &data,

            USBItem *parentItem = nullptr);
    ~USBItem();

    void appendChild(USBItem *child);

    USBItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    USBItem *parentItem();

private:
    QList<USBItem*> m_childItems;
    USBItem *m_parentItem;

    // Columns
    quint64 m_Timestamp;
    quint8 m_Pid;
    quint8 m_Dev;
    quint8 m_Endpoint;
    quint16 m_CRC;
    quint16 m_FrameNumber;
    quint32 m_DataLen;
    QByteArray m_Data;
};

#endif // USBITEM_H
