#ifndef USBTRANSACTION_H
#define USBTRANSACTION_H

#include "usbrecord.h"
#include "usbpacket.h"

class USBTransaction : public USBRecord
{
public:
    USBTransaction(USBPacket* token, USBPacket* data, USBPacket* handshake);

    QVariant data(int column) const;
    QBrush background() const;
    QFont font(int column) const;
    const QString asciiData();

private:
    USBPacket* m_token;
    USBPacket* m_data;
    USBPacket* m_handshake;
};

#endif // USBTRANSACTION_H
