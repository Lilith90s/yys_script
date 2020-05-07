#pragma once
#include <core.hpp>
#include <QPoint>
#include <Windows.h>
class QImage;
class QColor;

class PointFinder
{
public:
	/**
	 * \brief 将QT的point转换为mfc的point
	 * \param point 待转换的坐标
	 * \return mfc格式的point
	 */
	static LPARAM TransaltePointToLPARAM(QPoint point);

	/**
	 * \brief 查找界面中探索的点
	 * \return 查找结果
	 */
	static QPoint get_discovery_pos(HWND hd);

	static QPoint get_explore_pos(HWND hd);

	static bool check_color(QColor& color1,QColor& color2);

	static bool check_image(QImage& src,QImage& dst,QPoint& pos);

	static QPoint find_pos(HWND hd ,QString& dst_name);

	static IplImage *qimage_to_iplimage(const QImage* image);
};

