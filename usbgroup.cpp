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
        case 0:
            return m_first->getPidStr();
        case 1:
            return m_first->m_Timestamp;
        case 2:
            return QString(""); // FIXME only for SOF
        case 3:
            return QString("");
        case 4:
            return QString("");
        case 5:
            return QString("[Frames: %1-%2]")
                .arg(m_first->m_FrameNumber)
                .arg(m_last->m_FrameNumber);
        default:
            return QVariant();
    }
}
