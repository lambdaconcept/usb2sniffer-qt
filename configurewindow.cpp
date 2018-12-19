#include "configurewindow.h"
#include "ui_configurewindow.h"

#include <QDirIterator>

ConfigureWindow::ConfigureWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigureWindow)
{
    ui->setupUi(this);

    connect(ui->groupPackets, &QGroupBox::toggled, ui->groupToken, &QGroupBox::setChecked);
    connect(ui->groupPackets, &QGroupBox::toggled, ui->groupData, &QGroupBox::setChecked);
    connect(ui->groupPackets, &QGroupBox::toggled, ui->groupHandshake, &QGroupBox::setChecked);
    connect(ui->groupPackets, &QGroupBox::toggled, ui->groupSpecial, &QGroupBox::setChecked);

    connect(ui->groupToken, &QGroupBox::toggled, ui->checkIN, &QCheckBox::setChecked);
    connect(ui->groupToken, &QGroupBox::toggled, ui->checkOUT, &QCheckBox::setChecked);
    connect(ui->groupToken, &QGroupBox::toggled, ui->checkSOF, &QCheckBox::setChecked);
    connect(ui->groupToken, &QGroupBox::toggled, ui->checkSETUP, &QCheckBox::setChecked);

    connect(ui->groupData, &QGroupBox::toggled, ui->checkDATA0, &QCheckBox::setChecked);
    connect(ui->groupData, &QGroupBox::toggled, ui->checkDATA1, &QCheckBox::setChecked);
    connect(ui->groupData, &QGroupBox::toggled, ui->checkDATA2, &QCheckBox::setChecked);
    connect(ui->groupData, &QGroupBox::toggled, ui->checkMDATA, &QCheckBox::setChecked);

    connect(ui->groupHandshake, &QGroupBox::toggled, ui->checkACK, &QCheckBox::setChecked);
    connect(ui->groupHandshake, &QGroupBox::toggled, ui->checkNAK, &QCheckBox::setChecked);
    connect(ui->groupHandshake, &QGroupBox::toggled, ui->checkSTALL, &QCheckBox::setChecked);
    connect(ui->groupHandshake, &QGroupBox::toggled, ui->checkNYET, &QCheckBox::setChecked);

    connect(ui->groupSpecial, &QGroupBox::toggled, ui->checkPREERR, &QCheckBox::setChecked);
    connect(ui->groupSpecial, &QGroupBox::toggled, ui->checkSPLIT, &QCheckBox::setChecked);
    connect(ui->groupSpecial, &QGroupBox::toggled, ui->checkPING, &QCheckBox::setChecked);
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

    /* Restore capture configuration */

    ui->checkRxCmd->setChecked(m_config.rx_cmd);

    ui->groupPackets->setChecked(gsPackets);
    ui->groupToken->setChecked(gsToken);
    ui->groupData->setChecked(gsData);
    ui->groupHandshake->setChecked(gsHandshake);
    ui->groupSpecial->setChecked(gsSpecial);

    int32_t mask = m_config.pid_mask;

    ui->checkIN->setChecked(!(mask & CaptureMask::IN));
    ui->checkOUT->setChecked(!(mask & CaptureMask::OUT));
    ui->checkSOF->setChecked(!(mask & CaptureMask::SOF));
    ui->checkSETUP->setChecked(!(mask & CaptureMask::SETUP));
    ui->checkDATA0->setChecked(!(mask & CaptureMask::DATA0));
    ui->checkDATA1->setChecked(!(mask & CaptureMask::DATA1));
    ui->checkDATA2->setChecked(!(mask & CaptureMask::DATA2));
    ui->checkMDATA->setChecked(!(mask & CaptureMask::MDATA));
    ui->checkACK->setChecked(!(mask & CaptureMask::ACK));
    ui->checkNAK->setChecked(!(mask & CaptureMask::NAK));
    ui->checkSTALL->setChecked(!(mask & CaptureMask::STALL));
    ui->checkNYET->setChecked(!(mask & CaptureMask::NYET));
    ui->checkPREERR->setChecked(!(mask & CaptureMask::PRE_ERR));
    ui->checkSPLIT->setChecked(!(mask & CaptureMask::SPLIT));
    ui->checkPING->setChecked(!(mask & CaptureMask::PING));

    QDialog::open();
}

void ConfigureWindow::accept()
{
    /* Update configuration object based on user input */

    m_config.device = ui->comboDevice->currentText();
    m_config.rx_cmd = ui->checkRxCmd->checkState();

    int32_t mask = 0;

    if (!ui->checkIN->checkState())
        mask |= CaptureMask::IN;
    if (!ui->checkOUT->checkState())
        mask |= CaptureMask::OUT;
    if (!ui->checkSOF->checkState())
        mask |= CaptureMask::SOF;
    if (!ui->checkSETUP->checkState())
        mask |= CaptureMask::SETUP;
    if (!ui->checkDATA0->checkState())
        mask |= CaptureMask::DATA0;
    if (!ui->checkDATA1->checkState())
        mask |= CaptureMask::DATA1;
    if (!ui->checkDATA2->checkState())
        mask |= CaptureMask::DATA2;
    if (!ui->checkMDATA->checkState())
        mask |= CaptureMask::MDATA;
    if (!ui->checkACK->checkState())
        mask |= CaptureMask::ACK;
    if (!ui->checkNAK->checkState())
        mask |= CaptureMask::NAK;
    if (!ui->checkSTALL->checkState())
        mask |= CaptureMask::STALL;
    if (!ui->checkNYET->checkState())
        mask |= CaptureMask::NYET;
    if (!ui->checkPREERR->checkState())
        mask |= CaptureMask::PRE_ERR;
    if (!ui->checkSPLIT->checkState())
        mask |= CaptureMask::SPLIT;
    if (!ui->checkPING->checkState())
        mask |= CaptureMask::PING;

    m_config.pid_mask = mask;

    /* Store group box states */

    gsPackets = ui->groupPackets->isChecked();
    gsToken = ui->groupToken->isChecked();
    gsData = ui->groupData->isChecked();
    gsHandshake = ui->groupHandshake->isChecked();
    gsSpecial = ui->groupSpecial->isChecked();

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
