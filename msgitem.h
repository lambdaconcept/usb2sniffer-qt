#ifndef MSGITEM_H
#define MSGITEM_H

#include <QList>

class MSGItem
{
public:
    explicit MSGItem(MSGItem *parentItem = nullptr);
    ~MSGItem();

    void appendChild(MSGItem *child);
    MSGItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant headerData(int column) const;
    int row() const;
    MSGItem *parentItem();

    QVariant data(int column) const;

private:
    QList<MSGItem*> m_childItems;
    MSGItem *m_parentItem;
};

#endif // MSGITEM_H
