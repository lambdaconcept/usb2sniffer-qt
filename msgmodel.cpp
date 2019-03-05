#include "msgmodel.h"
#include "msgitem.h"

MSGModel::MSGModel(QObject *parent) : QAbstractItemModel(parent)
{
    m_rootItem = new MSGItem(0, 0, 0);
}

MSGModel::~MSGModel()
{
    delete m_rootItem;
}

int MSGModel::addMessage(uint64_t ts, uint8_t type, uint8_t val)
{
    int size;

    size = m_rootItem->childCount();
    beginInsertRows(QModelIndex(), size, size);
    m_rootItem->appendChild(new MSGItem(ts, type, val, m_rootItem));
    endInsertRows();

    return true;
}

QModelIndex MSGModel::index(int row, int column, const QModelIndex &parent)
            const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    MSGItem *parentItem;

    if (!parent.isValid())
        parentItem = m_rootItem;
    else
        parentItem = static_cast<MSGItem*>(parent.internalPointer());

    MSGItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex MSGModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    MSGItem *childItem = static_cast<MSGItem*>(index.internalPointer());
    MSGItem *parentItem = childItem->parentItem();

    if (parentItem == m_rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int MSGModel::rowCount(const QModelIndex &parent) const
{
    MSGItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = m_rootItem;
    else
        parentItem = static_cast<MSGItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int MSGModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<MSGItem*>(parent.internalPointer())->columnCount();
    else
        return m_rootItem->columnCount();
}

QVariant MSGModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    MSGItem *item = static_cast<MSGItem*>(index.internalPointer());

    switch(role) {
        case Qt::DisplayRole:
            return item->data(index.column());
        default:
            return QVariant();
    }
}

Qt::ItemFlags MSGModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index);
}

QVariant MSGModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return m_rootItem->headerData(section);

    return QVariant();
}
