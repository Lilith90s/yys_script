// ReSharper disable CppClangTidyMiscMisplacedConst
#include "FSM.h"
#include <QDebug>
#include "PointFinder.h"


/**
 * \brief 
 * \param hd 
 */
FSM::FSM(const HWND hd)
	:transition_(Transition::NONE)
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
		case NONE: break;
		case EXPLORE:
			Explore();
			break;
		case WAITING: break;
		default: ;
		}
	}	
}

void FSM::SetTransition(const Transition transition)
{
	this->transition_ = transition;
}

void FSM::Explore() const
{
	if (hd_)
	{
		auto pos = PointFinder::get_explore_pos(hd_);
		qDebug() << pos;
		if (pos.x() != -1)
		{

		}
		send_click(pos);
	}
	else
	{
		
	}
}
void FSM::send_click(QPoint& pos) const
{
	SendMessage(hd_, WM_LBUTTONDOWN, MK_LBUTTON, PointFinder::TransaltePointToLPARAM(pos));
	SendMessage(hd_, WM_LBUTTONUP, 0, PointFinder::TransaltePointToLPARAM(pos));
}
