#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "configurewindow.h"
#include "filterwindow.h"
#include "aboutwindow.h"
#include "capture.h"

#include "usbmodel.h"
#include "usbitem.h"
#include "usbproxy.h"
#include "usbgroup.h"
#include "usbpacket.h"
#include "usbtransaction.h"
#include "usbaggregator.h"
#include "msgmodel.h"
#include "msgitem.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "parser/parse.h"

#ifdef __cplusplus
}
#endif

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void displayDeviceNotFound();
    void displayDeviceDisconnected();
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void loadFile(QString file);

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void loadFileDialog();
    void saveFile();
    void exportAsPcap();
    void exportAsCsv();
    void exit();

    void startCapture();
    void stopCapture();
    void newSession();
    void captureFinished();

    void setFilter();
    /* search */
    QByteArray parseSearch(const QString &text);
    void nextSearch();
    void prevSearch();
    bool eventFilter(QObject* obj, QEvent *event);

    void updateAscii(const QModelIndex& index);
    void updateDetails(const QModelIndex& index);
    void updateRecordsStats(int number);

private:
    Ui::MainWindow *ui;
    ConfigureWindow *configWindow;
    FilterWindow *filterWindow;
    AboutWindow *aboutWindow;

    USBModel *currentModel = nullptr;
    USBProxy *currentProxy = nullptr;
    MSGModel *currentMsg = nullptr;

    CaptureThread *captureThread = nullptr;
    bool fileSaved = true; /* Used for warning on exit */

    struct usb_session_s *usb_sess = nullptr;

    QByteArray dataBuffer;
    QByteArray packetBuffer;
};

#endif // MAINWINDOW_H
