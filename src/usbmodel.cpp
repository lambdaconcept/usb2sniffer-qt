#include "usbmodel.h"
#include "usbitem.h"

#include <iostream>

USBModel::USBModel(QObject *parent) : QAbstractItemModel(parent)
{
    m_rootItem = new USBItem(new USBPacket(0, QByteArray()));

    m_aggregator.setRoot(m_rootItem);
}

USBModel::~USBModel()
{
    delete m_rootItem; // FIXME
}

int USBModel::addPacket(USBPacket *packet, bool nodeUpdate)
{
    /* Push packet to aggregator */
    m_aggregator.append(packet);
    if (nodeUpdate) {
        updateNodes();
        emit numberPopulated(m_aggregator.count());
    }

    return true;
}

void USBModel::updateNumberPopulated()
{
    emit numberPopulated(m_aggregator.count());
}

int USBModel::lastPacket()
{
    m_aggregator.done();
    updateNodes();

    return true;
}

void USBModel::updateNodes()
{
    int size;
    USBItem *child;

    /* Add new nodes from aggregator, if any */
    auto pendingCount = m_aggregator.getPendingCount();
    size = m_rootItem->childCount();

    if (pendingCount > 0) {
        beginInsertRows(QModelIndex(), size, size+pendingCount-1);

        while(m_aggregator.getPending(&child))
        {
            m_rootItem->appendChild(child);
        }

        endInsertRows();
    }
}

QModelIndex USBModel::index(int row, int column, const QModelIndex &parent)
            const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    USBItem *parentItem;

    if (!parent.isValid())
        parentItem = m_rootItem;
    else
        parentItem = static_cast<USBItem*>(parent.internalPointer());

    USBItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex USBModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    USBItem *childItem = static_cast<USBItem*>(index.internalPointer());
    USBItem *parentItem = childItem->parentItem();

    if (parentItem == m_rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int USBModel::rowCount(const QModelIndex &parent) const
{
    USBItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = m_rootItem;
    else
        parentItem = static_cast<USBItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int USBModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<USBItem*>(parent.internalPointer())->columnCount();
    else
        return m_rootItem->columnCount();
}

QVariant USBModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    USBItem *item = static_cast<USBItem*>(index.internalPointer());

    switch(role) {
        case Qt::DisplayRole:
            return item->data(index.column());
        case Qt::BackgroundRole:
            return item->background();
        case Qt::FontRole:
            return item->font(index.column());
        default:
            return QVariant();
    }
}

quint8 USBModel::getPid(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    USBItem *item = static_cast<USBItem*>(index.internalPointer());

    return item->getPid();
}

Qt::ItemFlags USBModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}

QVariant USBModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return m_rootItem->headerData(section);

    return QVariant();
}

const USBAggregator& USBModel::getAggregator() const
{
    return m_aggregator;
}

QModelIndex USBModel::runSearch(const QByteArray &search, QList<QModelIndex> *dest)
{
    QList<USBItem*> list;
    m_rootItem->searchRecursive(search, list);
    if (list.isEmpty()) {
        return QModelIndex();
    }

    /* Build model indexes */
    QList<QModelIndex> searchList;
    QList<USBItem*>::const_iterator it;
    for (it=list.constBegin(); it!=list.constEnd(); it++) {
        USBItem *item = *it;
        searchList.append(createIndex(item->row(), 0, item));
    }

    if (dest) {
        dest->append(searchList);
    }

    return searchList.value(0);
}
