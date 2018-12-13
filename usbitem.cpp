#include "usbitem.h"

const QVector<QString> USBItem::s_header = {
    "Record",
    "Timestamp",
    "Device",
    "Endpoint",
    "Length",
    "Summary",
    // Status
    // Error
};

USBItem::USBItem(USBPacket *record, USBItem *parentItem)
{
    m_parentItem = parentItem;
    m_record = record;
}

USBItem::~USBItem()
{
    qDeleteAll(m_childItems);
}

void USBItem::appendChild(USBItem *item)
{
    m_childItems.append(item);
}

USBItem *USBItem::child(int row)
{
    return m_childItems.value(row);
}

int USBItem::childCount() const
{
    return m_childItems.count();
}

int USBItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<USBItem*>(this));

    return 0;
}

int USBItem::columnCount() const
{
    return s_header.count();
}

QVariant USBItem::data(int column) const
{
    switch(column)
    {
        case 0:
            return m_record->getPidStr();
        case 1:
            return m_record->m_Timestamp;
        case 2:
            return QString("%1").arg(m_record->m_Dev, 2, 16, QChar('0'));
        case 3:
            return QString("%1").arg(m_record->m_Endpoint, 2, 16, QChar('0'));
        case 4:
            return m_record->m_Data.count();
        case 5:
            if(m_record->getPid() == PID_SOF) {
                return QString("Frame: %1").arg(m_record->m_FrameNumber);
            }
            return m_record->m_Data.toHex(' ');
        default:
            return QVariant();
    }
}

QVariant USBItem::headerData(int column) const
{
    return s_header.value(column);
}

USBItem *USBItem::parentItem()
{
    return m_parentItem;
}

QString formatHexdump(const QByteArray &data) {
    QString out;

    char ascii[17];
    int i, j;
    int addr = 0;

    ascii[16] = '\0';
    for (i = 0; i < data.size(); ++i) {
        if ((i % 16) == 0) {
            out += QString("%1  ").arg(addr, 4, 16, QChar('0'));
            addr += 16;
        }

        out += QString("%1 ").arg(static_cast<unsigned char>(data[i]), 2, 16, QChar('0'));
        if (data[i] >= ' ' && data[i] <= '~') {
            ascii[i % 16] = data[i];
        } else {
            ascii[i % 16] = '.';
        }
        if ((i+1) % 8 == 0 || i+1 == data.size()) {
            out += " ";
            if ((i+1) % 16 == 0) {
                out += "|";
                out += ascii;
                out += "|\n";
            } else if (i+1 == data.size()) {
                ascii[(i+1) % 16] = '\0';
                if ((i+1) % 16 <= 8) {
                    out += " ";
                }
                for (j = (i+1) % 16; j < 16; ++j) {
                    out += "   ";
                }
                out += "|";
                out += ascii;
                out += "|\n";
            }
        }
    }

    return out;
}

const QString USBItem::asciiData()
{
    return formatHexdump(m_record->m_Packet);
}

const QString USBItem::details()
{
    QString details;

    switch(m_record->getType())
    {
    case PID_TYPE_SPECIAL:
        break;

    case PID_TYPE_TOKEN:
        if(m_record->getPid() == PID_SOF) {
            details = QString("PID: 0x%1\nFrame No: %2\nCRC5: 0x%3\n")
                .arg(m_record->m_Pid, 2, 16, QChar('0'))
                .arg(m_record->m_FrameNumber)
                .arg(m_record->m_CRC, 2, 16, QChar('0'));
        }
        else {
            details = QString("PID: 0x%1\nDevice: %2\nEndpoint: %3\nCRC5: 0x%4\n")
                .arg(m_record->m_Pid, 2, 16, QChar('0'))
                .arg(m_record->m_Dev, 2, 16, QChar('0'))
                .arg(m_record->m_Endpoint, 2, 16, QChar('0'))
                .arg(m_record->m_CRC, 2, 16, QChar('0'));
        }
        break;

    case PID_TYPE_HANDSHAKE:
        details = QString("PID: 0x%1\n")
            .arg(m_record->m_Pid, 2, 16, QChar('0'));
        break;

    case PID_TYPE_DATA:
        details = QString("PID: 0x%1\nLength: %2\nCRC16: 0x%3\n")
            .arg(m_record->m_Pid, 2, 16, QChar('0'))
            .arg(m_record->m_Data.count())
            .arg(m_record->m_CRC, 4, 16, QChar('0'));
        break;
    }

    return details;
}
