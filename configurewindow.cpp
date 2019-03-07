#include "configurewindow.h"
#include "ui_configurewindow.h"

#include <QDirIterator>

ConfigureWindow::ConfigureWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigureWindow)
{
    ui->setupUi(this);
}

ConfigureWindow::~ConfigureWindow()
{
    delete ui;
}

QStringList ConfigureWindow::listAvailableDevices()
{
    QStringList devices;
    QStringList filter = {"ft60x*"};
    QDirIterator it("/dev", filter, QDir::System);
    while (it.hasNext()) {
        devices << it.next();
    }
    return devices;
}

void ConfigureWindow::open()
{
    QString current = ui->comboDevice->currentText();

    /* Refresh devices list */

    ui->comboDevice->clear();
    QStringList devices = listAvailableDevices();
    ui->comboDevice->addItems(devices);

    /* Restore last device selection if still available */

    if (devices.contains(current)) {
        ui->comboDevice->setCurrentText(current);
    }

    QDialog::open();
}

void ConfigureWindow::accept()
{
    /* Update configuration object based on user input */

    m_config.device = ui->comboDevice->currentText();

    QDialog::accept();
}

void ConfigureWindow::autoConfig()
{
    /* If no device is selected, find the first available */

    if (m_config.device.isEmpty()) {
        QStringList devices = listAvailableDevices();
        m_config.device = devices.value(0);
    }
}
