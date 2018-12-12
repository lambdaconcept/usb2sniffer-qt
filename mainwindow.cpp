#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    USBItem *rootItem = new USBItem(0,0,0,0,0,0,0,QByteArray());
    rootItem->appendChild(new USBItem(0,0xa5,1,2,3,0,0,QByteArray(),rootItem));

    USBModel *usbModel = new USBModel(rootItem);

    ui->treeView->setModel(usbModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}
