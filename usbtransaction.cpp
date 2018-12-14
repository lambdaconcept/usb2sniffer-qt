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
        case 0:
            return QString("%1 Transaction").arg(m_token->getPidStr());
        case 1:
            return m_token->m_Timestamp;
        case 2:
            return QString("%1").arg(m_token->m_Dev, 2, 16, QChar('0'));
        case 3:
            return QString("%1").arg(m_token->m_Endpoint, 2, 16, QChar('0'));
        case 4:
            return m_data->m_Data.count();
        case 5:
            return m_data->m_Data.toHex(' ');
        default:
            return QVariant();
    }
}

const QString USBTransaction::asciiData()
{
    return formatHexdump(m_data->m_Data);
}
