#ifndef CONFIGUREWINDOW_H
#define CONFIGUREWINDOW_H

#include <QDialog>
#include <QStringList>

#include "capture.h"

namespace Ui {
class ConfigureWindow;
}

class ConfigureWindow : public QDialog
{
public:
    explicit ConfigureWindow(QWidget *parent = nullptr);
    ~ConfigureWindow();

    void accept();
    void open();

    QStringList listAvailableDevices();
    void autoConfig();

    CaptureConfig m_config;

private:
    Ui::ConfigureWindow *ui;
};

#endif // CONFIGUREWINDOW_H
