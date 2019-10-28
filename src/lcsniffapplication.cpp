#include "lcsniffapplication.h"

LCSniffApplication::LCSniffApplication(int &argc, char **argv) : QApplication(argc, argv)
{

}

bool LCSniffApplication::event(QEvent *event)
{
	if (event->type() == QEvent::FileOpen) {
		QFileOpenEvent *openEvent = static_cast<QFileOpenEvent *>(event);
		qDebug() << "Open file" << openEvent->file();
		emit fileEvent(openEvent->file());
	}

	return QApplication::event(event);
}