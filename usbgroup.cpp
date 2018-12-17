#include "usbgroup.h"

USBGroup::USBGroup(USBPacket* first, USBPacket *last)
{
    m_first = first;
    m_last = last;
}

QVariant USBGroup::data(int column) const
{
    switch(column)
    {
        case RECORD_NAME:
            return m_first->getPidStr();
        case RECORD_TS:
            return m_first->m_Timestamp;
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
