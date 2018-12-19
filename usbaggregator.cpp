#include "usbaggregator.h"
#include "usbgroup.h"
#include "usbtransaction.h"

USBAggregator::USBAggregator()
{
    m_root = new USBItem(new USBPacket(0, QByteArray()));  // FIXME
}

USBAggregator::~USBAggregator()
{
    // delete m_root; // FIXME
    qDeleteAll(m_packets);
}

USBPacket* USBAggregator::value(int i)
{
    return m_packets.value(i);
}

USBItem* USBAggregator::getRoot()
{
    return m_root;
}

int USBAggregator::count() const
{
    return m_packets.count();
}

void USBAggregator::done()
{
    endGroup();
    endTransaction();
}

void USBAggregator::endGroup()
{
    USBItem *node;
    USBRecord *record;

    int i = m_packets.count();

    /* Push existing SOF */

    if((_lastPid == PID_SOF) && (_start != i)) {
        record = new USBGroup(m_packets[_start], m_packets[i-1]);
        node = new USBItem(record, m_root);
        for (int j = _start; j < i; j++) {
            node->appendChild(new USBItem(m_packets[j], node));
        }
        m_root->appendChild(node);
    }

    _lastPid = 0;
}

void USBAggregator::endTransaction()
{
    USBItem *node;
    USBRecord *record;

    /* Push existing transactions */

    if (_token || _data || _handshake) {
        record = new USBTransaction(_token, _data, _handshake);
        node = new USBItem(record, m_root);
        if (_token) {
            node->appendChild(new USBItem(_token, node));
        }
        if (_data) {
            node->appendChild(new USBItem(_data, node));
        }
        if (_handshake) {
            node->appendChild(new USBItem(_handshake, node));
        }
        m_root->appendChild(node);
    }

    /* Reset state */

    _state = TRANS_IDLE;
    _token = nullptr;
    _data = nullptr;
    _handshake = nullptr;
}

void USBAggregator::append(USBPacket* packet)
{
    quint8 pid = 0;
    quint8 type = 0;

    int i = m_packets.count();

    pid = packet->getPid();
    type = packet->getType();

    /* Group SOF */

    if((_lastPid != pid) && (_start != i)) {
        endGroup();
        _start = i;
    }

    /* Group transactions */

    if((_state == TRANS_IDLE) && (type == PID_TYPE_TOKEN) && (pid != PID_SOF)) {
        _token = packet;
        _state = TRANS_TOKEN;
    } else if ((_state == TRANS_TOKEN) && (type == PID_TYPE_DATA)) {
        _data = packet;
        _state = TRANS_DATA;
    } else if ((_state == TRANS_TOKEN) && (type == PID_TYPE_HANDSHAKE)) {
        _handshake = packet;
        _state = TRANS_IDLE;
        endTransaction();
    } else if ((_state == TRANS_DATA) && (type == PID_TYPE_HANDSHAKE)) {
        _handshake = packet;
        _state = TRANS_IDLE;
        endTransaction();
    } else if ((_state == TRANS_DATA) && (type == PID_TYPE_TOKEN)) {
        /* Was isochronous */
        endTransaction();
        if (pid != PID_SOF) {
            _token = packet;
            _state = TRANS_TOKEN;
        }
    } else {
        /* FSM error */
        endTransaction();
    }

    _lastPid = pid;
    m_packets.append(packet);
}
