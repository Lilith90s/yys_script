#include "yys_script.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	yys_script w;
	w.show();
	w.run();
	return a.exec();
}
