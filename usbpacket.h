#ifndef USBPACKET_H
#define USBPACKET_H

#include <QVector>
#include <QString>
#include <QByteArray>

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

class USBPacket
{
public:
    explicit USBPacket(const quint64 timestamp,
                       const QByteArray& packet);

    void decode();
    quint8 getPid();
    quint8 getType();
    QString getPidStr();
    QString getTypeStr();

    static const QVector<QString> pidStr;
    static const QVector<QString> typeStr;

public:
    quint64 m_Timestamp;
    quint8 m_Pid = 0;
    quint8 m_Dev = 0;
    quint8 m_Endpoint = 0;
    quint16 m_CRC = 0;
    quint16 m_FrameNumber = 0;
    QByteArray m_Packet;
    QByteArray m_Data;
    quint8 m_Err = 0;
};

#endif // USBPACKET_H
