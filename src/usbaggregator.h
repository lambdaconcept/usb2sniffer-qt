#ifndef USBAGGREGATOR_H
#define USBAGGREGATOR_H

#include <QVector>

#include "usbitem.h"
#include "usbpacket.h"

#define TRANS_IDLE 0
#define TRANS_TOKEN 1
#define TRANS_DATA 2
#define TRANS_HANDSHAKE 3

class USBAggregator
{
public:
    USBAggregator();
    ~USBAggregator();

    int count() const;
    USBPacket* value(int i) const;
    void append(USBPacket* packet);
    void endTransaction();
    void endGroup();
    void done();
    void setRoot(USBItem* root);
    USBItem* getRoot() const;
    bool getPending(USBItem **item);
    int getPendingCount() const;

private:
    USBItem *m_root;
    QVector<USBPacket *> m_packets; // FIXME should inherit from QVector
    QList<USBItem *> m_pending;

    quint8 _lastPid = 0;
    int _start = 0;
    int _state = 0;
    USBPacket* _token = nullptr;
    USBPacket* _data = nullptr;
    USBPacket* _handshake = nullptr;
};

#endif // USBAGGREGATOR_H
