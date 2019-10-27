#ifndef LCSNIFFAPPLICATION_H
#define LCSNIFFAPPLICATION_H

#include <QApplication>
#include <QFileOpenEvent>
#include <QtDebug>

class LCSniffApplication : public QApplication
{
	Q_OBJECT

signals:
    void fileEvent(QString file);
public:
    LCSniffApplication(int &argc, char **argv);
    bool event(QEvent *event);
};

#endif /* LCSNIFFAPPLICATION_H */