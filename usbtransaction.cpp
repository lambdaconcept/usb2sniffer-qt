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
            return formatTimestamp(m_token->m_Timestamp);
        case RECORD_DEVICE:
            return QString("%1").arg(m_token->m_Dev, 2, 16, QChar('0'));
        case RECORD_ENDPOINT:
            return QString("%1").arg(m_token->m_Endpoint, 2, 16, QChar('0'));
        case RECORD_STATUS:
            if (m_handshake) {
                return m_handshake->getPidStr();
            } else if (m_token->getPid() == PID_SPLIT) {
                return QString("");
            } else {
                return QString("Incomplete");
            }
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
    int ack = 0;

    if(m_token) {
        if(m_handshake) {
            if (m_handshake->getPid() == PID_ACK) {
                ack = 1;
            }
        }

        switch(m_token->getPid()) {
            case PID_SETUP:
                return !ack ? QBrush(QColor(188, 170, 164)) : QBrush(QColor(141, 110, 99));
            case PID_IN:
                return !ack ? QBrush(QColor(165, 214, 167)) : QBrush(QColor(102, 187, 106));
            case PID_OUT:
                return !ack ? QBrush(QColor(144, 202, 249)) : QBrush(QColor(66, 165, 245));
            default:
                // XXX FIXME PID_SPLIT color not implemented
                return QBrush();
        }
    }
    return QBrush();
}

QFont USBTransaction::font(int column) const
{
    switch(column)
    {
        case RECORD_SUMMARY:
            return QFont(QString::fromUtf8("Monospace"));
        default:
            return QFont();
    }
}

const QString USBTransaction::asciiData()
{
    return m_data ? formatHexdump(m_data->m_Data) : "";
}

const QString USBTransaction::details()
{
    QString details;

    details += QString("%1 Transaction\t[%2]\n\n")
        .arg(m_token->getPidStr())
        .arg(m_handshake ? m_handshake->getPidStr() : "");

    details += QString("Token:\t%1\nData:\t%2\nHandshake:\t%3\n")
        .arg(m_token->getPidStr())
        .arg(m_data ? m_data->getPidStr() : "None")
        .arg(m_handshake ? m_handshake->getPidStr() : "None");

    return details;
}
