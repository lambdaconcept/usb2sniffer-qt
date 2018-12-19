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
    /* Save & Restore group box states */
    bool gsPackets = true;
    bool gsToken = true;
    bool gsData = true;
    bool gsHandshake = true;
    bool gsSpecial = true;
};

#endif // CONFIGUREWINDOW_H
