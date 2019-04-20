#ifndef USBMODEL_H
#define USBMODEL_H

#include <QAbstractItemModel>

#include "usbpacket.h"
#include "usbitem.h"
#include "usbaggregator.h"

class USBModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit USBModel(QObject *parent = nullptr);
    ~USBModel();

    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    /* custom API */
    int addPacket(USBPacket *packet, bool nodeUpdate = true);
    int lastPacket();
    void updateNodes();
    void updateNumberPopulated();
signals:
    void numberPopulated(int number);

private:
    USBAggregator m_aggregator;
    USBItem *m_rootItem;
};

#endif // USBMODEL_H
