#ifndef USBPACKET_H
#define USBPACKET_H

#include <QString>
#include <QByteArray>

class USBPacket
{
public:
    explicit USBPacket(const quint64 timestamp,
                       const quint8 pid,
                       const quint8 dev,
                       const quint8 endpoint,
                       const quint16 crc,
                       const quint16 frameNumber,
                       const quint32 dataLen,
                       const QByteArray &data);

    QString getPidStr();

public:
    quint64 m_Timestamp;
    quint8 m_Pid;
    quint8 m_Dev;
    quint8 m_Endpoint;
    quint16 m_CRC;
    quint16 m_FrameNumber;
    quint32 m_DataLen;
    QByteArray m_Data;
};

#endif // USBPACKET_H
