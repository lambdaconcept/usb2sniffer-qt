#include <QFileDialog>

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

USBItem* groupRecords(USBItem* root, const QVector<USBPacket*> packets)
{
    USBItem *node;
    USBRecord *record;
    quint8 pid = 0;
    quint8 lastPid = 0;
    int start = 0;

    for (int i = 0; i < packets.count(); i++) {
        pid = packets[i]->getPid();
        if(lastPid != pid) {
            if (start != i) {

                if(lastPid == PID_SOF) {
                    record = new USBGroup(packets[start], packets[i-1]);
                }
                else {
                    record = packets[start];
                }

                node = new USBItem(record, root); // FIXME
                for (int j = start; j < i; j++) {
                    node->appendChild(new USBItem(packets[j], node));
                }
                root->appendChild(node);
                start = i;
            }
        }
        lastPid = pid;
    }

    return root;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->addPermanentWidget(ui->statusPacketNum);

    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::updateAscii);
    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::updateDetails);

    loadFile(); // FIXME for dev
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::loadFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadFile()
{
    //QString file = QFileDialog::getOpenFileName(this,
    //    "Open File", "", "*.bin");
    QString file = "../output.bin"; // FIXME for dev

    FILE *in;
    int len;
    char *buf;
    char *data;
    unsigned long long int timestamp;

    in = fopen(file.toUtf8().constData(), "rb");

    USBItem *rootItem;
    USBPacket *packet;
    USBModel *usbModel;

    QVector<USBPacket *> packetList;

    rootItem = new USBItem(new USBPacket(0, QByteArray()));

    while(!feof(in)){
        fread(&len, 1, sizeof(int), in);
        buf = static_cast<char *>(malloc(len));
        fread(buf, 1, len, in);

        memcpy(&len, buf, sizeof(int));
        memcpy(&timestamp, buf + sizeof(int), 8);
        data = buf + 12;

        packet = new USBPacket(timestamp, QByteArray(data, len));
        packetList.append(packet);

        free(buf);
    }

    // rootItem->appendChild(new USBItem(packet, rootItem));
    rootItem = groupRecords(rootItem, packetList);

    usbModel = new USBModel(rootItem);
    ui->treeView->setModel(usbModel);
    ui->statusPacketNum->setText(QString("Records: %1").arg(packetList.count()));
}

void MainWindow::updateAscii(const QModelIndex& index)
{
    if (!index.isValid())
        return;

    USBItem *item = static_cast<USBItem*>(index.internalPointer());

    ui->textAsciiPacket->setPlainText(item->asciiPacket());
    ui->textAsciiData->setPlainText(item->asciiData());
}

void MainWindow::updateDetails(const QModelIndex& index)
{
    if (!index.isValid())
        return;

    USBItem *item = static_cast<USBItem*>(index.internalPointer());

    ui->textDetails->setPlainText(item->details());
}
