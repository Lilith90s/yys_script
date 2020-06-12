#include "yys_script.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>
int main(int argc, char *argv[])
{
	
	QApplication a(argc, argv);
	yys_script w;
#ifdef _DEBUG
	w.setWindowTitle(QString::fromLocal8Bit("“ı—Ù ¶∏®÷˙Ω≈±æ-≤‚ ‘∞Ê"));
#else
	w.setWindowTitle(QString::fromLocal8Bit("“ı—Ù ¶∏®÷˙Ω≈±æ-∑¢––∞Ê"));
#endif
	
	w.show();
	w.run();
	return a.exec();
}
