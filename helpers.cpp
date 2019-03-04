#include "helpers.h"

QString formatTimestamp(quint64 timestamp)
{
    quint64 ts = timestamp;
    uint ns = ts % 1000;
    ts = (ts - ns) / 1000;
    uint us = ts % 1000;
    ts = (ts - us) / 1000;
    uint ms = ts % 1000;
    ts = (ts - ms) / 1000;
    uint sec = ts % 60;
    ts = (ts - sec) / 60;
    uint min = ts;

    return QString("%1:%2:%3:%4:%5")
        .arg(min, 2, 10, QChar('0'))
        .arg(sec, 2, 10, QChar('0'))
        .arg(ms, 3, 10, QChar('0'))
        .arg(us, 3, 10, QChar('0'))
        .arg(ns, 3, 10, QChar('0'));
}

QString formatHexdump(const QByteArray &data) {
    QString out;

    char ascii[17];
    int i, j;
    int addr = 0;

    ascii[16] = '\0';
    for (i = 0; i < data.size(); ++i) {
        if ((i % 16) == 0) {
            out += QString("%1  ").arg(addr, 4, 16, QChar('0'));
            addr += 16;
        }

        out += QString("%1 ").arg(static_cast<unsigned char>(data[i]), 2, 16, QChar('0'));
        if (data[i] >= ' ' && data[i] <= '~') {
            ascii[i % 16] = data[i];
        } else {
            ascii[i % 16] = '.';
        }
        if ((i+1) % 8 == 0 || i+1 == data.size()) {
            out += " ";
            if ((i+1) % 16 == 0) {
                out += "|";
                out += ascii;
                out += "|\n";
            } else if (i+1 == data.size()) {
                ascii[(i+1) % 16] = '\0';
                if ((i+1) % 16 <= 8) {
                    out += " ";
                }
                for (j = (i+1) % 16; j < 16; ++j) {
                    out += "   ";
                }
                out += "|";
                out += ascii;
                out += "|\n";
            }
        }
    }

    return out;
}
