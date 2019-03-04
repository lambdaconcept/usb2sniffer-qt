#ifndef MSGITEM_H
#define MSGITEM_H

#include <QList>

#define MSG_TS      0
#define MSG_TYPE    1
#define MSG_VALUE   2

class MSGItem
{
public:
    explicit MSGItem(uint64_t ts, uint8_t type, uint8_t val, MSGItem *parentItem = nullptr);
    ~MSGItem();

    void appendChild(MSGItem *child);
    MSGItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant headerData(int column) const;
    int row() const;
    MSGItem *parentItem();

    QVariant data(int column) const;

    static const QVector<QString> s_header;

private:
    QList<MSGItem*> m_childItems;
    MSGItem *m_parentItem;

    uint64_t m_ts;
    uint8_t m_type;
    uint8_t m_val;
};

#endif // MSGITEM_H