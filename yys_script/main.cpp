#include "yys_script.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>
int main(int argc, char *argv[])
{
	
	QApplication a(argc, argv);
	yys_script w;
#ifdef _DEBUG
	w.setWindowTitle(QString::fromLocal8Bit("����ʦ�����ű�-���԰�"));
#else
	w.setWindowTitle(QString::fromLocal8Bit("����ʦ�����ű�-���а�"));
#endif
	
	w.show();
	w.run();
	return a.exec();
}
