#pragma once
#include <QThread>
#include "Enum.h"
#include <Windows.h>
#include "ItemManger.h"
#include <vector>
class FSM: public QThread
{
	Q_OBJECT
public:
	/**
	 * \brief 
	 * \param hd 
	 */
	explicit FSM(HWND hd);
	
	void run() override;

	void set_explore_chapter(const QString chapter);

	void add_item_monitor(ItemBase* item);
	/**
	 * \brief 
	 * \param transition 
	 */
	void SetTransition(transition::Transition transition);
signals:
	void MessageSignal(QString &msg);
private:

	void Explore();

	auto send_click(QPoint& pos) const -> void;
	
	/**
	 * \brief 
	 */
	transition::Transition transition_;
	HWND hd_;
	QString chapter_str_;
	std::vector<ItemBase*> item_bases_;
};
