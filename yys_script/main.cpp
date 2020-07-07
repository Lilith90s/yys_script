#include "yys_script.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>
#include <QFile>
int main(int argc, char *argv[])
{
	
	QApplication a(argc, argv);
	yys_script w;
#ifdef _DEBUG
	w.setWindowTitle(QString::fromLocal8Bit("ÒõÑôÊ¦¸¨Öú½Å±¾-²âÊÔ°æ"));
#else
	w.setWindowTitle(QString::fromLocal8Bit("ÒõÑôÊ¦¸¨Öú½Å±¾-·¢ÐÐ°æ"));
#endif
	QFile f(":/qss/psblack.css");
	if (f.open(QIODevice::ReadOnly))
	{
		QString qss = f.readAll();
		QString paletteColor = qss.mid(20, 7);
		qApp->setPalette(QPalette(QColor(paletteColor)));
		qApp->setStyleSheet(qss);
	}
	f.close();
	w.show();
	w.run();
	return a.exec();
}
