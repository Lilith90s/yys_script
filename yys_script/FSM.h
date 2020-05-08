#pragma once
#include <QThread>
#include "Enum.h"
#include <Windows.h>

class FSM: public QThread
{
	
public:
	/**
	 * \brief 
	 * \param hd 
	 */
	explicit FSM(HWND hd);
	
	void run() override;

	void SetTransition(Transition transition);
signals:
	void MessageSignal(QString &msg);
private:

	void Explore() const;

	auto send_click(QPoint& pos) const -> void;
	
	/**
	 * \brief 
	 */
	Transition transition_;
	HWND hd_;
};
