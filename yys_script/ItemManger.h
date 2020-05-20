#pragma once
#include <QObject>
class ItemBase:public QObject
{
	Q_OBJECT
public:
	virtual QString item_name() = 0;
	virtual QString item_image_path() = 0;
	void add_num(const int i)
	{
		if (!i)
		{
			return;
		}
		num_i_ += i;
		emit num_changed(num_i_);
	};
	void set_num(const int i)
	{
		num_i_ = i;
		emit num_changed(num_i_);
	};
signals:
	void num_changed(int i);
private:
	int num_i_{0};
	
};

class BreakthroughTicketItem :public ItemBase
{
	QString item_name() override
	{
		return QString::fromLocal8Bit("Í»ÆÆÈ¯");
	}
	QString item_image_path() override
	{
		return "./assets/items/breakthrough_ticket.jpg";
	}
};
