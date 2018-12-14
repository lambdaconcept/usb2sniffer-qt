#ifndef USBAGGREGATOR_H
#define USBAGGREGATOR_H

#include <QVector>

#include "usbitem.h"
#include "usbpacket.h"

class USBAggregator
{
public:
    USBAggregator();

    USBItem* getRoot();
    int count() const;
    void append(USBPacket* packet);

private:
    USBItem *m_root;
    QVector<USBPacket *> m_packets;

    quint8 _lastPid = 0;
    int _start = 0;
    USBPacket* _token = nullptr;
    USBPacket* _data = nullptr;
    USBPacket* _handshake = nullptr;
};

#endif // USBAGGREGATOR_H
