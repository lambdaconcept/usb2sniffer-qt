#include "usbpacket.h"
#include "helpers.h"

USBPacket::USBPacket(const quint64 timestamp,
                     const QByteArray& packet)  // FIXME use ref or pointer ??
{
    m_Timestamp = timestamp;
    m_Packet = packet;

    decode();
}

const QVector<QString> USBPacket::pidStr = {
    "RESERVED",
    "OUT",
    "ACK",
    "DATA0",
    "PING",
    "SOF",
    "NYET",
    "DATA2",
    "SPLIT",
    "IN",
    "NAK",
    "DATA1",
    "ERR/PRE",
    "SETUP",
    "STALL",
    "MDATA"
};

const QVector<QString> USBPacket::typeStr = {
    "SPECIAL",
    "TOKEN",
    "HANDSHAKE",
    "DATA"
};

quint8 USBPacket::getPid() const
{
    return (m_Pid & 0xf);
}

quint8 USBPacket::getType() const
{
    return (m_Pid & 0x3);
}

QString USBPacket::getPidStr() const
{
    return pidStr[(m_Pid & 0xf)];
}

QString USBPacket::getTypeStr() const
{
    return typeStr[(m_Pid & 0x3)];
}

void USBPacket::decode()
{
    int len;
    char *data;
    unsigned char pid;
    unsigned char pid_type;

    if((m_Packet[0] & 0xf) != (~(m_Packet[0] >> 4) & 0xf) ){
        m_Err = 1; // FIXME
        return;
    }

    pid = m_Packet[0] & 0xf;
    pid_type = pid & 0x3;

    m_Pid = m_Packet[0] & 0xff;

    switch(pid_type){
        case PID_TYPE_SPECIAL:
            switch(pid) {
                case PID_PRE:
                case PID_SPLIT:
                case PID_PING:
                    break;
            }
            break;

        case PID_TYPE_TOKEN:
            m_CRC = ((m_Packet[2] & 0xff) >> 3) & 0x1f;
            switch(pid){
                case PID_OUT:
                case PID_IN:
                case PID_SETUP:
                    m_Dev = m_Packet[1] & 0x7f;
                    m_Endpoint = (((m_Packet[2] & 0x7) << 1) | (( m_Packet[1] & 0x80) >> 7)) & 0xf;
                    break;
                case PID_SOF:
                    m_FrameNumber = ((m_Packet[1] & 0xff) | ((m_Packet[2] & 0x7) << 8)) & 0x7ff;
                    break;
            }
            break;

        case PID_TYPE_HANDSHAKE:
            switch(pid) {
                case PID_ACK:
                case PID_NAK:
                case PID_STALL:
                case PID_NYET:
                    break;
            }
            break;

        case PID_TYPE_DATA:
            len = m_Packet.count();
            data = m_Packet.data() + 1;
            m_Data.setRawData(data, len-3);
            m_CRC = (m_Packet[len-2] & 0xff) | ((m_Packet[len-1] & 0xff) << 8);
            switch(pid){
                case PID_DATA0:
                case PID_DATA1:
                case PID_DATA2:
                case PID_MDATA:
                    break;
            }
            break;
    }
}

QVariant USBPacket::data(int column) const
{
    switch(column)
    {
        case RECORD_NAME:
            return QString("%1 Packet").arg(getPidStr());
        case RECORD_TS:
            return formatTimestamp(m_Timestamp);
        case RECORD_DEVICE:
            return QString("%1").arg(m_Dev, 2, 16, QChar('0'));
        case RECORD_ENDPOINT:
            return QString("%1").arg(m_Endpoint, 2, 16, QChar('0'));
        case RECORD_STATUS:
            return QString("");
        case RECORD_LENGTH:
            return m_Packet.count();
        case RECORD_SUMMARY:
            if(getPid() == PID_SOF) {
                return QString("Frame: %1").arg(m_FrameNumber);
            }
            return m_Packet.toHex(' ');
        default:
            return QVariant();
    }
}

const QString USBPacket::asciiData()
{
    return formatHexdump(m_Data);
}

const QString USBPacket::asciiPacket()
{
    return formatHexdump(m_Packet);
}

const QString USBPacket::details()
{
    QString details;

    switch(getType())
    {
    case PID_TYPE_SPECIAL:
        if(getPid() == PID_SPLIT) {
            details = QString("PID:\t0x%1\n")
                .arg(m_Pid, 2, 16, QChar('0'));
        }
        break;

    case PID_TYPE_TOKEN:
        if(getPid() == PID_SOF) {
            details = QString("PID:\t0x%1\nFrame No:\t%2\nCRC5:\t0x%3\n")
                .arg(m_Pid, 2, 16, QChar('0'))
                .arg(m_FrameNumber)
                .arg(m_CRC, 2, 16, QChar('0'));
        }
        else {
            details = QString("PID:\t0x%1\nDevice:\t%2\nEndpoint:\t%3\nCRC5:\t0x%4\n")
                .arg(m_Pid, 2, 16, QChar('0'))
                .arg(m_Dev, 2, 16, QChar('0'))
                .arg(m_Endpoint, 2, 16, QChar('0'))
                .arg(m_CRC, 2, 16, QChar('0'));
        }
        break;

    case PID_TYPE_HANDSHAKE:
        details = QString("PID:\t0x%1\n")
            .arg(m_Pid, 2, 16, QChar('0'));
        break;

    case PID_TYPE_DATA:
        details = QString("PID:\t0x%1\nLength:\t%2\nCRC16:\t0x%3\n")
            .arg(m_Pid, 2, 16, QChar('0'))
            .arg(m_Data.count())
            .arg(m_CRC, 4, 16, QChar('0'));
        break;
    }

    return details;
}
