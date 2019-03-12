#include <QFileDialog>
#include <QMessageBox>

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

MSGItem* createSampleMsg()
{
    MSGItem *rootItem = new MSGItem(0, 0, 0);

    rootItem->appendChild(new MSGItem(0, 0, 0, rootItem));
    rootItem->appendChild(new MSGItem(0, 0, 0, rootItem));
    rootItem->appendChild(new MSGItem(0, 0, 0, rootItem));

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

    // loadFile(); // FIXME for dev

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
    delete currentProxy;
    delete currentModel;
    delete currentMsg;

    delete configWindow;
    delete ui;
}

void MainWindow::setFilter()
{
    if (currentProxy) {
        currentProxy->setFilter(filterWindow->getFilter());
    }
}

void MainWindow::newSession()
{
    /* Put data into model */

    USBModel *usbModel = new USBModel();
    connect(usbModel, &USBModel::numberPopulated, this, &MainWindow::updateRecordsStats);

    /* Create proxy view for filtering */

    USBProxy *proxyModel = new USBProxy(this);
    proxyModel->setFilter(filterWindow->getFilter());
    proxyModel->setSourceModel(usbModel);

    QItemSelectionModel *m = ui->treeView->selectionModel();
    ui->treeView->setModel(proxyModel);
    ui->treeView->setColumnWidth(0, 300);
    ui->treeView->setColumnWidth(1, 150);

    /* Put raw messages into model */

    MSGModel *msgModel = new MSGModel();
    ui->messageView->setModel(msgModel);
    ui->messageView->setColumnWidth(0, 150);

    /* Delete previous data */

    m->deleteLater();
    delete currentProxy;
    delete currentModel;
    delete currentMsg;

    currentProxy = proxyModel;
    currentModel = usbModel;
    currentMsg = msgModel;
}

void MainWindow::captureFinished()
{
    /* enable / disable action buttons */

    ui->actionStart->setEnabled(true);
    ui->actionStop->setEnabled(false);

    ui->actionOpen->setEnabled(true);
    ui->actionSave_As->setEnabled(true);
    ui->actionConfigure->setEnabled(true);

    captureThread->deleteLater();
    captureThread = nullptr;
}

void MainWindow::startCapture()
{
    if (captureThread == nullptr) {

        /* free old and create new session */

        if (usb_sess) {
            usb_free_session(usb_sess);
            usb_sess = nullptr;
        }
        usb_sess = usb_new_session();
        newSession();

        /* run capture in a separate thread */

        captureThread = new CaptureThread();
        captureThread->setModel(currentModel, currentMsg);
        captureThread->setUsbSession(usb_sess);

        connect(captureThread, &CaptureThread::finished, this, &MainWindow::captureFinished);

        configWindow->autoConfig();
        captureThread->setConfig(&configWindow->m_config);
        captureThread->start();

        /* enable / disable action buttons */

        ui->actionStart->setEnabled(false);
        ui->actionStop->setEnabled(true);

        fileSaved = false;
        ui->actionOpen->setEnabled(false);
        ui->actionSave_As->setEnabled(false);
        ui->actionConfigure->setEnabled(false);
    }
}

void MainWindow::stopCapture()
{
    if ((captureThread != nullptr) && (captureThread->isRunning())) {
        captureThread->stop();
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
        "Save File", "", "*.usb");

    FILE *out;

    out = fopen(file.toUtf8().constData(), "wb");
    if(!out) {
        return;
    }

    if (usb_sess) {
        usb_write_session(usb_sess, out);
    }

    fclose(out);

    fileSaved = true;
}

void MainWindow::loadFile()
{
    FILE *in;
    size_t len;
    uint32_t plen;
    uint8_t buf[512];
    uint8_t swp[512];
    uint8_t type;
    uint8_t val;
    uint64_t ts;

    QString file = QFileDialog::getOpenFileName(this,
        "Open File", "", "*.usb");

    in = fopen(file.toUtf8().constData(), "rb");
    if(!in) {
        return;
    }

    /* free old and create new session */

    if (usb_sess) {
        usb_free_session(usb_sess);
        usb_sess = nullptr;
    }
    usb_sess = usb_new_session();
    newSession();

    while(!feof(in)){
        len = fread(buf, 1, 512, in);
        if(len < 0)
            return;

        /* file stored in byte swapped format */
        usb_swap_bytes(swp, buf, len);

        usb_add_data(usb_sess, swp, len);

        while(usb_read_data(usb_sess, &type, &val, &ts)){
            currentMsg->addMessage(ts, type, val);
        }
        while(usb_read_packet(usb_sess, &type, swp, &plen, &ts)){
            currentModel->addPacket(new USBPacket(ts, QByteArray((char *)swp, plen)));
        }
    }

    currentModel->lastPacket();
    fclose(in);

    fileSaved = true;
    ui->actionSave_As->setEnabled(false);
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

void MainWindow::updateRecordsStats(int number)
{
    ui->statusPacketNum->setText(QString("Records: %1").arg(number));
}
