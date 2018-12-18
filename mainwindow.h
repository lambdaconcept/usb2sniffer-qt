#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "configurewindow.h"

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
    void startCapture();
    void stopCapture();
    void handleResults(USBModel *usbModel);

    void updateAscii(const QModelIndex& index);
    void updateDetails(const QModelIndex& index);

private:
    Ui::MainWindow *ui;
    ConfigureWindow *configWindow;
};

#endif // MAINWINDOW_H
