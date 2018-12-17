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

const QString USBTransaction::asciiData()
{
    return m_data ? formatHexdump(m_data->m_Data) : "";
}
