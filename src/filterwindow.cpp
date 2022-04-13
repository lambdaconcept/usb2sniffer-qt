#include "filterwindow.h"
#include "ui_filterwindow.h"

FilterWindow::FilterWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterWindow)
{
    ui->setupUi(this);
}

FilterWindow::~FilterWindow()
{
    delete ui;
}

const USBProxyFilter* FilterWindow::getFilter() const
{
    return &m_filter;
}

void FilterWindow::open()
{
    /* Restore filter configuration */

    ui->checkSOF->setChecked(m_filter.sof);
    ui->checkSPLIT->setChecked(m_filter.split);

    ui->checkNAKIN->setChecked(m_filter.nakIn);
    ui->checkNAKOUT->setChecked(m_filter.nakOut);
    ui->checkNAKSETUP->setChecked(m_filter.nakSetup);
    ui->checkNAKPING->setChecked(m_filter.nakPing);

    ui->lineDevice->setText(m_filter.device);
    ui->lineEndpoint->setText(m_filter.endpoint);

    QDialog::open();
}

void FilterWindow::accept()
{
    bool intConversionResult;
    /* Update configuration object based on user input */

    m_filter.sof = ui->checkSOF->checkState();
    m_filter.split = ui->checkSPLIT->checkState();

    m_filter.nakIn = ui->checkNAKIN->checkState();
    m_filter.nakOut = ui->checkNAKOUT->checkState();
    m_filter.nakSetup = ui->checkNAKSETUP->checkState();
    m_filter.nakPing = ui->checkNAKPING->checkState();

    m_filter.device = ui->lineDevice->text();
    m_filter.deviceNum = m_filter.device.toInt(&intConversionResult);
    if (!intConversionResult) {
        m_filter.deviceNum = - 1;
    }

    m_filter.endpoint = ui->lineEndpoint->text();
    m_filter.endpointNum = m_filter.endpoint.toInt(&intConversionResult);
    if (!intConversionResult) {
        m_filter.endpointNum = - 1;
    }

    QDialog::accept();
}
