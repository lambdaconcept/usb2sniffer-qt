#ifndef FILTERWINDOW_H
#define FILTERWINDOW_H

#include <QDialog>

#include "usbproxy.h"

namespace Ui {
class FilterWindow;
}

class FilterWindow : public QDialog
{
    Q_OBJECT

public:
    explicit FilterWindow(QWidget *parent = nullptr);
    ~FilterWindow();

    void accept();
    void open();

    const USBProxyFilter *getFilter() const;

private:
    Ui::FilterWindow *ui;
    USBProxyFilter m_filter;
};

#endif // FILTERWINDOW_H
