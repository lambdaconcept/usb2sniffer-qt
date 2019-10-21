#ifndef USBPACKET_H
#define USBPACKET_H

#include <QVector>
#include <QString>
#include <QByteArray>

#include "usbrecord.h"

#define PID_RESERVED 0x0
#define PID_OUT	     0x1
#define PID_IN	     0x9
#define PID_SOF	     0x5
#define PID_SETUP    0xD
#define PID_DATA0    0x3
#define PID_DATA1    0xB
#define PID_DATA2    0x7
#define PID_MDATA    0xF
#define PID_ACK	     0x2
#define PID_NAK      0xA
#define PID_STALL    0xE
#define PID_NYET     0x6
#define PID_PRE	     0xC
#define PID_ERR	     0xC
#define PID_SPLIT    0x8
#define PID_PING     0x4

#define PID_TYPE_SPECIAL   0
#define PID_TYPE_TOKEN     1
#define PID_TYPE_HANDSHAKE 2
#define PID_TYPE_DATA      3

#define ERR_OK      0
#define ERR_DECODE  1
#define ERR_FSM     2

class USBPacket : public USBRecord
{
public:
    explicit USBPacket(const quint64 timestamp,
                       const QByteArray& packet);

    void decode();
    quint8 getPid() const;
    quint8 getType() const;
    QString getPidStr() const;
    QString getTypeStr() const;

    static const QVector<QString> pidStr;
    static const QVector<QString> typeStr;

    QVariant data(int column) const;
    QBrush background() const;
    const QString asciiData();
    const QString asciiPacket();
    const QString details();
    QPair<QByteArray, QByteArray> recordData();

public:
    quint64 m_Timestamp;
    quint8 m_Pid = 0;
    quint8 m_Dev = 0;
    quint8 m_Endpoint = 0;
    quint16 m_CRC = 0;
    quint16 m_FrameNumber = 0;
    QByteArray m_Packet;
    QByteArray m_Data;
    quint8 m_Err = ERR_OK;
};

#endif // USBPACKET_H
