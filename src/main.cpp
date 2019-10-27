#include "lcsniffapplication.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    LCSniffApplication app(argc, argv);
    MainWindow win;

    QObject::connect(&app, SIGNAL(fileEvent(QString)), &win, SLOT(loadFile(QString)));
    win.showMaximized();

    return app.exec();
}
