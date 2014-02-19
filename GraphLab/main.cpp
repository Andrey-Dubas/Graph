#include "graphiclab.h"
#include <QtGui/QApplication>



int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GraphicLab w;
	w.show();
	return a.exec();
}
