#include "usbgroup.h"
#include "helpers.h"

USBGroup::USBGroup(int count, USBPacket* first, USBPacket *last)
{
    m_count = count;
    m_first = first;
    m_last = last;
}

QVariant USBGroup::data(int column) const
{
    switch(column)
    {
        case RECORD_NAME:
            return QString("%1 Group [%2]")
                .arg(m_first->getPidStr())
                .arg(m_count);
        case RECORD_TS:
            return formatTimestamp(m_first->m_Timestamp);
        case RECORD_DEVICE:
            return QString(""); // FIXME only for SOF
        case RECORD_ENDPOINT:
            return QString("");
        case RECORD_STATUS:
            return QString("");
        case RECORD_LENGTH:
            return QString("");
        case RECORD_SUMMARY:
            return QString("[Frames: %1-%2]")
                .arg(m_first->m_FrameNumber)
                .arg(m_last->m_FrameNumber);
        default:
            return QVariant();
    }
}

QBrush USBGroup::background() const
{
    return QBrush(QColor(255, 241, 118));
}

const QString USBGroup::details()
{
    QString details;

    details += QString("%1 Group\n\n")
        .arg(m_first->getPidStr());

    details += QString("Number of Frames:\t%1\nFirst Frame Number:\t%2\nLast Frame Number:\t%3\n")
        .arg(m_count)
        .arg(m_first->m_FrameNumber)
        .arg(m_last->m_FrameNumber);

    return details;
}

quint8 USBGroup::getPid() const
{
    return m_first->getPid();
}

bool USBGroup::matchForFilter(const USBProxyFilter *filter) const
{
    switch (m_first->getPid()) {
    case PID_SOF:
        return filter->sof;
        break;
    default:
        return true;
        break;
    }
}
