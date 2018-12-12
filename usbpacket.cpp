#include "usbpacket.h"

USBPacket::USBPacket(const quint64 timestamp,
                     const quint8 pid,
                     const quint8 dev,
                     const quint8 endpoint,
                     const quint16 crc,
                     const quint16 frameNumber,
                     const quint32 dataLen,
                     const QByteArray &data)
{

    m_Timestamp = timestamp;
    m_Pid = pid;
    m_Dev = dev;
    m_Endpoint = endpoint;
    m_CRC = crc;
    m_FrameNumber = frameNumber;
    m_DataLen = dataLen;
    m_Data = data;
}

QString USBPacket::getPidStr()
{
    return QString("%1").arg(m_Pid, 2, 16);
}
