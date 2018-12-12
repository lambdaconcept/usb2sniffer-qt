#include "mainwindow.h"
#include "ui_mainwindow.h"

USBItem* createSampleData()
{
    USBItem *rootItem = new USBItem(new USBPacket(0,0,0,0,0,0,0,QByteArray()));
    rootItem->appendChild(new USBItem(new USBPacket(0,0xa5,1,2,3,0,0,QByteArray()),rootItem));
    USBItem *node = new USBItem(new USBPacket(0,0xb2,1,2,3,0,0,QByteArray()),rootItem);
    node->appendChild(new USBItem(new USBPacket(0,0xb2,1,2,3,0,0,QByteArray()),node));
    rootItem->appendChild(node);
    rootItem->appendChild(new USBItem(new USBPacket(0,0xc3,1,2,3,0,8,QByteArray::fromHex("8006000100004000")),rootItem));

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
