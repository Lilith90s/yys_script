#pragma once
#include <core.hpp>
#include <QPoint>
#include <Windows.h>
#include "ItemManger.h"
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

	static QPoint get_chapter_pos(HWND hd,QString chapter);

	static QPoint get_explore_pos(HWND hd);

	static QPoint get_challenge_pos(HWND hd);

	static QPoint get_prepare_pos(HWND hd);

	static QPoint get_challenge_result_pos(HWND hd);

	static QPoint get_boss_pos(HWND hd);

	static QPoint get_chest_pos(HWND hd);

	static void count_items(HWND hd, std::vector<ItemBase*>& items_vector);

	static int count_item_number(HWND hd,ItemBase* item);
	
	static bool check_color(QColor& color1,QColor& color2);

	static bool check_image(QImage& src,QImage& dst,QPoint& pos);

	static QPoint find_pos(HWND hd ,QString& dst_name);

	static IplImage *qimage_to_iplimage(const QImage* image);

	static bool is_valid_pos(QPoint &pos);

public:
	static float pr_score;  // ƥ����ֵ
};

