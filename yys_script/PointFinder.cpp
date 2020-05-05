#include "PointFinder.h"

#include <QApplication>
#include <QPixmap>
#include <QScreen>
#include <QImage>
#include <QDebug>

LPARAM PointFinder::TransaltePointToLPARAM(QPoint point)
{
	LPARAM ret = point.y();
	ret = ret << 16;
	ret += point.x();
	return ret;
}

auto PointFinder::get_discovery_pos(HWND hd) -> QPoint
{
	auto screen = QGuiApplication::primaryScreen();
	const auto map = screen->grabWindow(reinterpret_cast<WId>(hd)/*,578,122,41,39*/);
	// map.save("discovery.jpg","JPG");
	auto screenshots = map.toImage();
	QImage discoveryImage("discovery.jpg");
	// qDebug() << screenshots.pixelColor(578, 122);
	// qDebug() << discoveryImage.pixelColor(0, 0);
	for (auto i = 0; i < screenshots.width(); ++i)
	{
		for (auto j=0;j<screenshots.height();++j)
		{
			if (screenshots.pixelColor(i,j) == discoveryImage.pixelColor(0,0))
			{
				// 查找到起始点
				if (check_image(screenshots, discoveryImage, QPoint(i, j)))
				{
					return QPoint(i, j);
				}
			}
		}
	}
	
	return QPoint(-1,-1);
}

bool PointFinder::check_color(QColor& color1, QColor& color2)
{
	const auto r1 = color1.red();
	const auto b1 = color1.blue();
	const auto g1 = color1.green();
	const auto r2 = color2.red();
	const auto b2 = color2.blue();
	const auto g2 = color2.green();
	if (r1 == r2 && b1 == b2 && g1 == g2)
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool PointFinder::check_image(QImage& src, QImage& dst, QPoint& pos)
{
	int same_point = 0;
	auto total_point = dst.width()*dst.height();
	int x1 = pos.x(), y1 = pos.y(), x2 = 0, y2 = 0;
	while (x1 < src.width() && y1 < src.height() && x2 < dst.width() && y2 < dst.height())
	{
		if (check_color(src.pixelColor(x1, y1), dst.pixelColor(x2, y2)))
		{	
			same_point++;
		}
		x1++;
		y1++;
		x2++;
		y2++;
	}
	qDebug() << same_point << "/" << total_point;
	if (static_cast<double>(same_point)/total_point < 0.95)
	{
		return false;
	}
	return true;
}
