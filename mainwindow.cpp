#include "mainwindow.h"
#include "ui_mainwindow.h"

USBItem* createSampleData()
{
    USBItem *rootItem = new USBItem(new USBPacket(0, QByteArray()));

    USBItem *node = new USBItem(new USBPacket(1, QByteArray::fromHex("555342")), rootItem);

    node->appendChild(new USBItem(new USBPacket(1, QByteArray::fromHex("698218")), node));
    node->appendChild(new USBItem(new USBPacket(2, QByteArray::fromHex("4b5553425310")), node));
    node->appendChild(new USBItem(new USBPacket(3, QByteArray::fromHex("d2")), node));

    rootItem->appendChild(node);

    return rootItem;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    USBItem *rootItem = createSampleData();
    USBModel *usbModel = new USBModel(rootItem);

    ui->treeView->setModel(usbModel);

    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::updateAscii);
    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::updateDetails);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateAscii(const QModelIndex& index)
{
    if (!index.isValid())
        return;

    USBItem *item = static_cast<USBItem*>(index.internalPointer());

    ui->textAscii->setPlainText(item->asciiData());
}

void MainWindow::updateDetails(const QModelIndex& index)
{
    if (!index.isValid())
        return;

    USBItem *item = static_cast<USBItem*>(index.internalPointer());

    ui->textDetails->setPlainText(item->details());
}
