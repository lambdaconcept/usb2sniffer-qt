#ifndef USBGROUP_H
#define USBGROUP_H

#include "usbrecord.h"
#include "usbpacket.h"

class USBGroup : public USBRecord
{
public:
    USBGroup(USBPacket* first, USBPacket *last);

    QVariant data(int column) const;

private:
    USBPacket *m_first;
    USBPacket *m_last;
};

#endif // USBGROUP_H
