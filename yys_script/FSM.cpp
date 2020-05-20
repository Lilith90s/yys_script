// ReSharper disable CppClangTidyMiscMisplacedConst
#include "FSM.h"
#include <QDebug>
#include "PointFinder.h"
#include "Status.h"


/**
 * \brief 
 * \param hd 
 */
FSM::FSM(const HWND hd)
	:transition_(transition::Transition::NONE)
	,hd_(hd)
{
	
}

void FSM::run()
{
	
	// 启动线程
	while (true)
	{
		switch (transition_)
		{
		case transition::NONE: break;
		case transition::EXPLORE:
			Explore();
			break;
		case transition::WAITING: break;
		default: ;
		}
	}	
}

void FSM::set_explore_chapter(const QString chapter)
{
	chapter_str_ = chapter;
}

void FSM::add_item_monitor(ItemBase* item)
{
	item_bases_.push_back(item);
}

void FSM::SetTransition(const transition::Transition transition)
{
	this->transition_ = transition;
}

void FSM::Explore()
{
	static auto explore_status = Status<explore::Explore>(explore::NONE,explore::WAIT_FOR_CHAPTER_CLICK);
	static auto is_boss = false;		// boss需要切换到拾取宝箱
	static auto is_first_monster = true; // 第一只怪需要等待加载时间
	RECT rect;
	GetWindowRect(hd_, &rect);
	if (hd_)
	{
		QPoint pos;
		switch (explore_status.status_now)
		{
		case explore::NONE: break;

		case explore::WAIT_FOR_CHAPTER_CLICK:
		{
			Sleep(3000);
			if (explore_status.status_pre != explore::WAIT_FOR_CHAPTER_CLICK)
			{
				auto msg = QString::fromLocal8Bit("探索第") + chapter_str_ +QString::fromLocal8Bit( "章");
				emit MessageSignal(msg); 
			}
			pos = PointFinder::get_chapter_pos(hd_, chapter_str_);
			while (pos == QPoint(0,0))
			{
				pos = PointFinder::get_chapter_pos(hd_, chapter_str_);
			}
			explore_status.change_status(explore::WAIT_FOR_EXPLORE_CLICK);
			break;	
		}
		case explore::WAIT_FOR_EXPLORE_CLICK:
		{
			Sleep(2000);
			pos = PointFinder::get_explore_pos(hd_);
			// 切换到查找怪物
			while (pos.x() == 0 && pos.y() == 0)
			{
				pos = PointFinder::get_explore_pos(hd_);
			}
			explore_status.change_status(explore::FINDING_MONSTER);
			is_first_monster = true;
			break;
		}	
		case explore::FINDING_MONSTER:
		{
			if (is_first_monster)
			{
				// 睡眠3s等待
				Sleep(3000);
				is_first_monster = false;
			}
			// 优先查找首领
			pos = PointFinder::get_boss_pos(hd_);
			if (pos.x() != 0 && pos.y() != 0)
			{
				if (explore_status.status_pre != explore::FINDING_LEADER)
				{
					emit MessageSignal(QString::fromLocal8Bit("发现首领!"));
				}
				is_boss = true;
				explore_status.change_status(explore::IN_CHALLENGING);
				break;
			}

			// 未找到首领，开始查找普通怪物
			if (explore_status.status_pre != explore::FINDING_MONSTER)
			{
				emit MessageSignal(QString::fromLocal8Bit("查找怪物..."));
			}	
			pos = PointFinder::get_challenge_pos(hd_);
			if (pos.x() == 0 && pos.y() == 0)
			{
				// 屏幕上没有怪了，切换到走动
				explore_status.change_status(explore::WALKING);
			}
			else
			{
				// 切换到挑战中
				explore_status.change_status(explore::IN_CHALLENGING);
			}

			break;
		}
		case explore::IN_CHALLENGING:
		{
			if (explore_status.status_pre != explore::IN_CHALLENGING)
			{
				emit MessageSignal(QString::fromLocal8Bit("打怪中.."));
			}
			// 睡眠10s，等待准备
			Sleep(2000);
			auto prepare_pos = PointFinder::get_prepare_pos(hd_);
			// while (!PointFinder::is_valid_pos(prepare_pos))
			// {
			// 	prepare_pos = PointFinder::get_prepare_pos(hd_);
			// }
			send_click(prepare_pos);
				
			pos = PointFinder::get_challenge_result_pos(hd_);
			while (pos.x() == 0 && pos.y() == 0)
			{
				// 维持挑战
				pos = PointFinder::get_challenge_result_pos(hd_);
			}
			Sleep(1500);
			PointFinder::count_items(hd_, item_bases_);
			send_click(pos);
			if (is_boss == true)
			{
				// 挑战结束，等待5s加载
				Sleep(5000);
				// 打的是boss怪,切换到拾取宝箱状态
				explore_status.change_status(explore::PICKING_UP_CHEST);
				is_boss = false;
			}
			else
			{
				explore_status.change_status(explore::FINDING_MONSTER);
			}
			return;
			break;
		}
		case explore::FINDING_LEADER:
		{
			break;
		}
		case explore::WALKING:
		{
			if (explore_status.status_pre != explore::WALKING)
			{
				emit MessageSignal(QString::fromLocal8Bit("当前屏幕没有怪物，走动中..."));
			}
			
			// 向前走

			pos = QPoint(1000, 500);
			// 等待2秒，让人物走到地点
			Sleep(2000);
			// 回到查找怪物模式
			explore_status.change_status(explore::FINDING_MONSTER);
			break;
		};
		case explore::PICKING_UP_CHEST:
		{
			
			if (explore_status.status_pre != explore::PICKING_UP_CHEST)
			{
				emit MessageSignal(QString::fromLocal8Bit("拾取宝箱中..."));
			}
			auto chapter_pos = PointFinder::get_chapter_pos(hd_, chapter_str_); // 章节位置
			auto explore_pos = PointFinder::get_explore_pos(hd_);		// 探索按钮位置
			while (true) // 判断是否宝箱拾取完毕并且到达选择章节界面
			{
				// 继续查找宝箱
				pos = PointFinder::get_chest_pos(hd_);
				// 捡起宝箱
				send_click(pos);
				// 点击确定，取消宝物模态框
				Sleep(1500);
				PointFinder::count_items(hd_, item_bases_);
				send_click(QPoint(rect.bottom - 120, rect.right / 2));
				// 检查是否出现探索按钮
				explore_pos = PointFinder::get_explore_pos(hd_);
				if (PointFinder::is_valid_pos(explore_pos))
				{
					auto msg = QString::fromLocal8Bit("宝箱拾取完毕，开始下一次挑战...");
					emit MessageSignal(msg);

					// 一次副本完毕，直接返回重来
					explore_status.change_status(explore::WAIT_FOR_EXPLORE_CLICK);
					return;
				}

				// 检查是否出现章节按钮，由于不会返回到
				chapter_pos = PointFinder::get_chapter_pos(hd_, chapter_str_);
				if (PointFinder::is_valid_pos(chapter_pos))
				{
					auto msg = QString::fromLocal8Bit("宝箱拾取完毕，有发现！");
					emit MessageSignal(msg);
					// 发现宝箱，返回选取章节界面
					explore_status.change_status(explore::WAIT_FOR_CHAPTER_CLICK);
					return;
				}
			}
		}

		default:;
		}
		
		// qDebug() << pos;
		if (pos.x() != 0 && pos.y() != 0)
		{
			// send_click(QPoint(rect.bottom - 120, rect.right / 2));
			send_click(pos);
		}

	}
}
void FSM::send_click(QPoint& pos) const
{
	SendMessage(hd_, WM_LBUTTONDOWN, MK_LBUTTON, PointFinder::TransaltePointToLPARAM(pos));
	SendMessage(hd_, WM_LBUTTONUP, 0, PointFinder::TransaltePointToLPARAM(pos));
}
