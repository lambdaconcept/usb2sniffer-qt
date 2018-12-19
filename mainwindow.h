#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "configurewindow.h"
#include "capture.h"

#include "usbmodel.h"
#include "usbitem.h"
#include "usbgroup.h"
#include "usbpacket.h"
#include "usbtransaction.h"
#include "usbaggregator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void loadFile();
    void saveFile();
    void exit();

    void startCapture();
    void stopCapture();
    void handleResults(USBAggregator *usbAggregator);
    void captureFinished();

    void updateAscii(const QModelIndex& index);
    void updateDetails(const QModelIndex& index);

private:
    Ui::MainWindow *ui;
    ConfigureWindow *configWindow;

    USBModel *currentModel = nullptr;
    USBAggregator *currentAggregator = nullptr;

    CaptureThread *captureThread = nullptr;
    bool fileSaved = true; /* Used for warning on exit */
};

#endif // MAINWINDOW_H
