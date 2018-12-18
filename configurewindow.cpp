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

void ConfigureWindow::open()
{
    ui->comboDevice->clear();

    QStringList filter = {"ft60x*"};
    QDirIterator it("/dev", filter, QDir::System);
    while (it.hasNext()) {
        ui->comboDevice->addItem(it.next());
    }

    QDialog::open();
}

void ConfigureWindow::accept()
{
    m_config.device = ui->comboDevice->currentText();
    m_config.rx_cmd = ui->checkRxCmd->checkState();

    QDialog::accept();
}

void ConfigureWindow::autoConfig()
{
    /* If no device is selected, find the first available */

    if (m_config.device.isEmpty()) {
        QStringList filter = {"ft60x*"};
        QDirIterator it("/dev", filter, QDir::System);
        if(it.hasNext()) {
            m_config.device = it.next();
        }
    }
}
