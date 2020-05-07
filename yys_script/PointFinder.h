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
	 * \brief ��QT��pointת��Ϊmfc��point
	 * \param point ��ת��������
	 * \return mfc��ʽ��point
	 */
	static LPARAM TransaltePointToLPARAM(QPoint point);

	/**
	 * \brief ���ҽ�����̽���ĵ�
	 * \return ���ҽ��
	 */
	static QPoint get_discovery_pos(HWND hd);

	static QPoint get_explore_pos(HWND hd);

	static bool check_color(QColor& color1,QColor& color2);

	static bool check_image(QImage& src,QImage& dst,QPoint& pos);

	static QPoint find_pos(HWND hd ,QString& dst_name);

	static IplImage *qimage_to_iplimage(const QImage* image);
};

