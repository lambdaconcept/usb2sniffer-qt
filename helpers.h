#ifndef HELPERS_H
#define HELPERS_H

#include <QString>
#include <QByteArray>

QString formatTimestamp(quint64 timestamp);
QString formatHexdump(const QByteArray &data);

#endif // HELPERS_H
