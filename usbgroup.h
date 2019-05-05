#ifndef USBGROUP_H
#define USBGROUP_H

#include "usbrecord.h"
#include "usbpacket.h"

class USBGroup : public USBRecord
{
public:
    USBGroup(int count, USBPacket* first, USBPacket *last);

    QVariant data(int column) const;
    QBrush background() const;
    const QString details();
	quint8 getPid() const;
private:
    int m_count;
    USBPacket *m_first;
    USBPacket *m_last;
};

#endif // USBGROUP_H
