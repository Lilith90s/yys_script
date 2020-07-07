#include "TextFinder.h"

TextFinder::TextFinder()
{

}

TextFinder* TextFinder::instance_ = nullptr;
TextFinder& TextFinder::getInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new TextFinder;
	}
	return *instance_;
}

QString TextFinder::detector_text(QRect& rect)
{
	QString ret;
	return ret;
}
