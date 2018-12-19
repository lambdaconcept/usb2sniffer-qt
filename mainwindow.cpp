#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <unistd.h> // FIXME

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
    ui->statusBar->addPermanentWidget(ui->statusPacketNum);

    configWindow = new ConfigureWindow(this);
    filterWindow = new FilterWindow(this);

    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::updateAscii);
    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::updateDetails);

    loadFile(); // FIXME for dev

    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::loadFile);
    connect(ui->actionSave_As, &QAction::triggered, this, &MainWindow::saveFile);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::exit);

    connect(ui->actionConfigure, &QAction::triggered, configWindow, &ConfigureWindow::open);
    connect(ui->actionStart, &QAction::triggered, this, &MainWindow::startCapture);
    connect(ui->actionStop, &QAction::triggered, this, &MainWindow::stopCapture);

    connect(ui->actionFilter, &QAction::triggered, filterWindow, &FilterWindow::open);
    connect(filterWindow, &FilterWindow::accepted, this, &MainWindow::setFilter);
}

MainWindow::~MainWindow()
{
    delete configWindow;
    delete ui;
}

void MainWindow::setFilter()
{
    if (currentProxy) {
        qDebug() << "setFilter\n";
        currentProxy->setFilter(filterWindow->getFilter());
    }
}

void MainWindow::handleRecords(USBAggregator* aggregator)
{
    ui->statusPacketNum->setText(QString("Records: %1").arg(aggregator->count()));

    /* Put data into model */

    USBModel *usbModel = new USBModel(aggregator->getRoot());
    USBProxy *proxyModel = new USBProxy(this);
    proxyModel->setFilter(filterWindow->getFilter());
    proxyModel->setSourceModel(usbModel);

    QItemSelectionModel *m = ui->treeView->selectionModel();
    ui->treeView->setModel(proxyModel);
    ui->treeView->setColumnWidth(0, 300);

    /* Delete previous data */

    m->deleteLater();
    delete currentProxy;
    delete currentModel;
    delete currentAggregator;
    currentProxy = proxyModel;
    currentModel = usbModel;
    currentAggregator = aggregator;
}

void MainWindow::captureFinished()
{
    ui->actionStart->setEnabled(true);
    ui->actionStop->setEnabled(false);

    captureThread->deleteLater();
    captureThread = nullptr;
}

void MainWindow::startCapture()
{
    if (captureThread == nullptr) {
        captureThread = new CaptureThread();

        connect(captureThread, &CaptureThread::resultReady, this, &MainWindow::handleRecords);
        connect(captureThread, &CaptureThread::finished, this, &MainWindow::captureFinished);

        configWindow->autoConfig();
        captureThread->setConfig(&configWindow->m_config);
        captureThread->start();

        ui->actionStart->setEnabled(false);
        ui->actionStop->setEnabled(true);

        fileSaved = false;
    }
}

void MainWindow::stopCapture()
{
    if ((captureThread != nullptr) && (captureThread->isRunning())) {
        // FIXME stop thread
    }
}


void MainWindow::exit()
{
    if (!fileSaved) {
        QMessageBox msgBox(this);
        msgBox.setText("Capture file not saved");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);

        switch (msgBox.exec()) {
          case QMessageBox::Save:
              saveFile();
              close();
              break;
          case QMessageBox::Discard:
              close();
              break;
          case QMessageBox::Cancel:
              break;
          default:
              break;
        }
    }
    else {
        close();
    }
}

void MainWindow::saveFile()
{
    QString file = QFileDialog::getSaveFileName(this,
        "Save File", "", "*.bin");

    FILE *out;
    unsigned int len;
    char *buf;
    unsigned long long int timestamp;

    out = fopen(file.toUtf8().constData(), "wb");
    if(!out) {
        return;
    }

    buf = static_cast<char *>(malloc(1024 + 12));

    USBPacket *packet;
    for (int i = 0; i < currentAggregator->count(); ++i) {
        packet = currentAggregator->value(i);

        len = packet->m_Packet.count();
        timestamp = packet->m_Timestamp;

        memcpy(buf, &len, sizeof(int));
        memcpy(buf + sizeof(int), &timestamp, 8);
        memcpy(buf + 12, packet->m_Packet.data(), len);

        len = (((len + 12) - 1) & 0xfffffffc) + 4; // align to next dword
        fwrite(&len, 1, sizeof(int), out);
        fwrite(buf, 1, len, out);
    }

    free(buf);
    fclose(out);

    fileSaved = true;
}

void MainWindow::loadFile()
{
    // QString file = QFileDialog::getOpenFileName(this,
    //    "Open File", "", "*.bin");
    QString file = "../output.bin"; // FIXME

    FILE *in;
    int len;
    size_t size;
    char *buf;
    char *data;
    unsigned long long int timestamp;

    in = fopen(file.toUtf8().constData(), "rb");
    if(!in) {
        return;
    }

    /* Read file and push packets in aggregator */

    USBAggregator *aggregator = new USBAggregator();

    while(!feof(in)){
        size = fread(&len, 1, sizeof(int), in);
        if (size < sizeof(int))
            break;
        buf = static_cast<char *>(malloc(len));
        size = fread(buf, 1, len, in);
        if (size < len) {
            free(buf);
            break;
        }

        memcpy(&len, buf, sizeof(int));
        memcpy(&timestamp, buf + sizeof(int), 8);
        data = buf + 12;

        aggregator->append(new USBPacket(timestamp, QByteArray(data, len)));  // FIXME ?

        free(buf);
    }
    aggregator->done();
    fclose(in);

    handleRecords(aggregator);

    fileSaved = true;
}

void MainWindow::updateAscii(const QModelIndex& index)
{
    if (!index.isValid())
        return;

    QModelIndex source = currentProxy->mapToSource(index);
    USBItem *item = static_cast<USBItem*>(source.internalPointer());

    ui->textAsciiPacket->setPlainText(item->asciiPacket());
    ui->textAsciiData->setPlainText(item->asciiData());
}

void MainWindow::updateDetails(const QModelIndex& index)
{
    if (!index.isValid())
        return;

    QModelIndex source = currentProxy->mapToSource(index);
    USBItem *item = static_cast<USBItem*>(source.internalPointer());

    ui->textDetails->setPlainText(item->details());
}
