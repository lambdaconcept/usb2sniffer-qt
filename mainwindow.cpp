#include "mainwindow.h"
#include "ui_mainwindow.h"

USBItem* createSampleData()
{
    USBItem *rootItem = new USBItem(0,0,0,0,0,0,0,QByteArray());
    rootItem->appendChild(new USBItem(0,0xa5,1,2,3,0,0,QByteArray(),rootItem));
    USBItem *node = new USBItem(0,0xb2,1,2,3,0,0,QByteArray(),rootItem);
    node->appendChild(new USBItem(0,0xb2,1,2,3,0,0,QByteArray(),node));
    rootItem->appendChild(node);
    rootItem->appendChild(new USBItem(0,0xc3,1,2,3,0,8,QByteArray::fromHex("8006000100004000"),rootItem));

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
}

MainWindow::~MainWindow()
{
    delete ui;
}
