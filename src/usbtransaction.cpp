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
            return m_data ? m_data->m_Data.toHex(' ') : QString("");
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
            case PID_PING:
                return !ack ? QBrush(QColor(255, 191, 226)) : QBrush(QColor(255, 123, 195));
            case PID_SPLIT:
                return !ack ? QBrush(QColor(255, 201, 154)) : QBrush(QColor(255, 174, 103));
            default:
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

quint8 USBTransaction::getPid() const
{
    return m_token->getPid();
}

QPair<QByteArray, QByteArray> USBTransaction::recordData()
{
    if (m_data) {
        return qMakePair(m_data->m_Data, emptyBuffer);
    } else {
        return qMakePair(emptyBuffer, emptyBuffer);
    }
}

bool USBTransaction::matchForFilter(const USBProxyFilter *filter) const
{
    /* Check device and endpoint numbers */
    if ((filter->deviceNum == -1 || m_token->m_Dev == filter->deviceNum)
        && (filter->endpointNum == -1 || m_token->m_Endpoint == filter->endpointNum)) {

        /* Check for NAK or Incomplete */
        if ((m_handshake && m_handshake->getPid() == PID_NAK) || (!m_handshake)) {
            switch (m_token->getPid()) {
            case PID_IN:
                return filter->nakIn;
            case PID_OUT:
                return filter->nakOut;
            case PID_SETUP:
                return filter->nakSetup;
            case PID_PING:
                return filter->nakPing;

            case PID_SPLIT:
                return filter->split;

            default:
                return true;
            }
        } else {
            return true;
        }
    } else {
        return false;
    }
}
