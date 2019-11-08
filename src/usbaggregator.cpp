#include <iostream>

#include "usbaggregator.h"
#include "usbgroup.h"
#include "usbtransaction.h"

USBAggregator::USBAggregator()
{

}

USBAggregator::~USBAggregator()
{
    qDeleteAll(m_packets);
}

USBPacket* USBAggregator::value(int i) const
{
    return m_packets.value(i);
}

int USBAggregator::count() const
{
    return m_packets.count();
}

void USBAggregator::setRoot(USBItem* root)
{
    m_root = root;
}

bool USBAggregator::getPending(USBItem **item)
{
    if (m_pending.isEmpty())
        return false;

    *item = m_pending.takeFirst();
    return true;
}

int USBAggregator::getPendingCount() const
{
    return m_pending.size();
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
        record = new USBGroup(i-_start, m_packets[_start], m_packets[i-1]);
        node = new USBItem(record, m_root);
        for (int j = _start; j < i; j++) {
            node->appendChild(new USBItem(m_packets[j], node));
        }
        m_pending.append(node);
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
        m_pending.append(node);
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
        /* Receive the first token */
        _token = packet;
        _state = TRANS_TOKEN;
    } else if ((_state == TRANS_TOKEN) && (type == PID_TYPE_DATA)) {
        /* Token followed by data */
        _data = packet;
        _state = TRANS_DATA;
    } else if ((_state == TRANS_TOKEN) && (type == PID_TYPE_HANDSHAKE)) {
        /* Token without data followed by handshake */
        _handshake = packet;
        _state = TRANS_IDLE;
        /* Done transaction */
        endTransaction();
    } else if ((_state == TRANS_DATA) && (type == PID_TYPE_HANDSHAKE)) {
        /* Token + data followed by handshake */
        _handshake = packet;
        _state = TRANS_IDLE;
        /* Done transaction */
        endTransaction();
    } else if ((_state == TRANS_DATA) && (type == PID_TYPE_TOKEN)) {
        /* Was isochronous */
        endTransaction();
        if (pid != PID_SOF) {
            _token = packet;
            _state = TRANS_TOKEN;
        }
    } else if ((_state == TRANS_TOKEN) && (type == PID_TYPE_TOKEN)) {
        /* Incomplete transaction */
        endTransaction();
        if (pid != PID_SOF) {
            _token = packet;
            _state = TRANS_TOKEN;
        }
    } else if (pid == PID_SPLIT) {
        /* Split transaction */
        endTransaction();
        _token = packet;
        endTransaction();
    } else if (pid == PID_PING) {
        /* Consider Ping as Special Token */
        endTransaction();
        _token = packet;
        _state = TRANS_TOKEN;
    } else if (pid == PID_SOF) {
        /* Catch SOF, nothing to do really */
    } else {
        /* FSM error */
        std::cout << "FSM error: unknown state (new PID: " <<
                     QString("%1").arg(pid, 2, 16, QChar('0')).toStdString()
                  << ") (state: " << _state << ")\n";
        endTransaction();

        /* We still want to show the error packet in the GUI */
        USBItem *node;
        packet->m_Err = ERR_FSM;
        node = new USBItem(packet, m_root);
        node->appendChild(new USBItem(packet, node));
        m_pending.append(node);
    }

    _lastPid = pid;
    m_packets.append(packet);
}
