#pragma once
#include <qstring.h>
#include <QRect>
class TextFinder
{
	static TextFinder& getInstance();

public:
	QString detector_text(QRect& rect);
private:
	TextFinder();
	
	static TextFinder* instance_;
};

