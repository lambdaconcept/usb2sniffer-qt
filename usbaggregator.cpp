#include "usbaggregator.h"
#include "usbgroup.h"
#include "usbtransaction.h"

USBAggregator::USBAggregator()
{
    m_root = new USBItem(new USBPacket(0, QByteArray()));  // FIXME
}

USBItem* USBAggregator::getRoot()
{
    return m_root;
}

int USBAggregator::count() const
{
    return m_packets.count();
}

void USBAggregator::append(USBPacket* packet)
{
    m_root->appendChild(new USBItem(packet, m_root));
}

/*
void USBAggregator::append(USBPacket* packet)
{
    USBItem *node;
    USBRecord *record;

    quint8 pid = 0;
    quint8 type = 0;

    int i = m_packets.count();

    pid = packet->getPid();
    type = packet->getType();
    if(_lastPid != pid) {
        if (_start != i) {

            if(type == PID_TYPE_TOKEN) {
                _token = packet;
                _data = nullptr;
                _handshake = nullptr;
            } else if (type == PID_TYPE_DATA) {
                _data = packet;
                _handshake = nullptr;
            } else if (type == PID_TYPE_HANDSHAKE) {
                _handshake = packet;
            } else {
                _token = nullptr;
                _data = nullptr;
                _handshake = nullptr;
            }

            if(_lastPid == PID_SOF) {
                record = new USBGroup(m_packets[_start], m_packets[i-1]);
                node = new USBItem(record, m_root);
                for (int j = _start; j < i; j++) {
                    node->appendChild(new USBItem(m_packets[j], node));
                }
                m_root->appendChild(node);
            }
            else if (_token && _data && _handshake) {
                record = new USBTransaction(_token, _data, _handshake);
                node = new USBItem(record, m_root);
                node->appendChild(new USBItem(_token, node));
                node->appendChild(new USBItem(_data, node));
                node->appendChild(new USBItem(_handshake, node));
                m_root->appendChild(node);
            }
            _start = i;
        }
    }
    _lastPid = pid;

    m_packets.append(packet);
}
*/
