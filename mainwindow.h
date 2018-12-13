#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "usbmodel.h"
#include "usbitem.h"
#include "usbpacket.h"

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

    void updateAscii(const QModelIndex& index);
    void updateDetails(const QModelIndex& index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
