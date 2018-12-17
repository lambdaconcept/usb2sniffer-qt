#include "usbtransaction.h"
#include "helpers.h"

USBTransaction::USBTransaction(USBPacket* token, USBPacket* data, USBPacket* handshake)
{
    m_token = token;
    m_data = data;
    m_handshake = handshake;
}

QVariant USBTransaction::data(int column) const
{
    switch(column)
    {
        case RECORD_NAME:
            return QString("%1 Transaction").arg(m_token->getPidStr());
        case RECORD_TS:
            return m_token->m_Timestamp;
        case RECORD_DEVICE:
            return QString("%1").arg(m_token->m_Dev, 2, 16, QChar('0'));
        case RECORD_ENDPOINT:
            return QString("%1").arg(m_token->m_Endpoint, 2, 16, QChar('0'));
        case RECORD_STATUS:
            return m_handshake ? m_handshake->getPidStr() : "";
        case RECORD_LENGTH:
            return m_data ? m_data->m_Data.count() : 0;
        case RECORD_SUMMARY:
            return m_data ? m_data->m_Data.toHex(' ') : "";
        default:
            return QVariant();
    }
}

QBrush USBTransaction::background() const
{
    int noack = 0;

    if(m_token) {
        if(m_handshake) {
            if (m_handshake->getPid() != PID_ACK) {
                noack = 1;
            }
        }

        switch(m_token->getPid()) {
            case PID_SETUP:
                return noack ? QBrush(QColor(188, 170, 164)) : QBrush(QColor(141, 110, 99));
            case PID_IN:
                return noack ? QBrush(QColor(165, 214, 167)) : QBrush(QColor(102, 187, 106));
            case PID_OUT:
                return noack ? QBrush(QColor(144, 202, 249)) : QBrush(QColor(66, 165, 245));
        }
    }
    return QBrush();
}

const QString USBTransaction::asciiData()
{
    return m_data ? formatHexdump(m_data->m_Data) : "";
}
