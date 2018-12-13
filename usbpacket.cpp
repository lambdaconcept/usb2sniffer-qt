#include "usbpacket.h"

USBPacket::USBPacket(const quint64 timestamp,
                     const QByteArray& packet)
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

quint8 USBPacket::getPid()
{
    return (m_Pid & 0xf);
}

quint8 USBPacket::getType()
{
    return (m_Pid & 0x3);
}

QString USBPacket::getPidStr()
{
    return pidStr[(m_Pid & 0xf)];
}

QString USBPacket::getTypeStr()
{
    return typeStr[(m_Pid & 0x3)];
}

void USBPacket::decode()
{
    unsigned char pid;
    unsigned char pid_type;

    if((m_Packet[0] & 0xf) != (~(m_Packet[0] >> 4) & 0xf) ){
        m_Err = 1; // FIXME
        return;
    }

    pid = m_Packet[0] & 0xF;
    pid_type = pid & 0x3;

    m_Pid = m_Packet[0];

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
            m_CRC = m_Packet[2] >> 3;
            switch(pid){
                case PID_OUT:
                case PID_IN:
                case PID_SETUP:
                    m_Dev = m_Packet[1] &0x7f;
                    m_Endpoint = ((m_Packet[2] & 0x7) << 1) | (( m_Packet[1] & 0x80) >> 7);
                    break;
                case PID_SOF:
                    m_FrameNumber = m_Packet[1] | ((m_Packet[2] & 0x7) << 8);
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
            m_Data.setRawData(m_Packet.data()+1, m_Packet.count()-3);
            m_CRC = m_Packet[m_Packet.count() - 2] | (m_Packet[m_Packet.count() - 1] << 8);
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
