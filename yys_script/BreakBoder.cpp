#include "BreakBoder.h"
#include  <QRect>
#include "PointFinder.h"

BreakBoder::BreakBoder(HWND hd)
	: hd(hd)
{
	check_point = {
		QRect(121,89,284,101), // 上左
		QRect(427,89,284,101), // 上中
		QRect(732,89,284,101), // 上右
		
		QRect(121,209,284,101), // 中左
		QRect(427,209,284,101), // 中间
		QRect(732,209,284,101), // 中右
		
		QRect(121,328,284,101), // 下左
		QRect(427,328,284,101), // 下中
		QRect(732,328,284,101), // 下右
	};
}

bool BreakBoder::make_challenge_failed(QRect &rect)
{
	challenge_action(rect);
	Sleep(1000);
	if (attack_action() == false)
	{
		return false;
	}
	Sleep(1500);
	quit_attack_action();
	return true;
}

void BreakBoder::challenge(QRect &rect)
{
	ChallengeStatus ret = Challenging;
	while (ret != Success)
	{
		challenge_action(rect);
		Sleep(1000);
		attack_action();
		Sleep(1500);
		ret = Challenging;
		while (ret == Challenging)
		{
			ret = get_challenge_result();
			
			Sleep(2000);
		}
		PointFinder::send_click(QPoint(620, 240), hd);
		Sleep(4000);
		switch (ret)
		{
		case Success: return;
		case Failed: 
			emit MessageSignal(QString::fromLocal8Bit("突破失败，重新突破！"));
			break;
		case Challenging: break;
		default: ;
		}
		
	}
	emit MessageSignal(QString::fromLocal8Bit("突破成功！！"));

}

void BreakBoder::challenge_action(QRect& rect)
{
	QPoint clear_pos(190, 40);
	PointFinder::send_click(clear_pos, hd);
	Sleep(500);
	QPoint click_pos = QPoint(rect.x()+rect.width()/2,rect.y()+rect.height()/2);
	PointFinder::send_click(click_pos,hd);
}

bool BreakBoder::attack_action()
{
	QPoint point(0,0);
	auto image_name = QString("./assets/breakboder/attack.jpg");
	point = PointFinder::find_pos(hd, image_name);
	if (PointFinder::is_valid_pos(point))
	{
		PointFinder::send_click(point, hd);
		return true;
	}
	
	return false;
}

void BreakBoder::quit_attack_action()
{
	QPoint quit_point(0, 0);
	while (!PointFinder::is_valid_pos(quit_point))
	{
		quit_point = PointFinder::find_pos(hd, QString("./assets/return.jpg"));
		Sleep(1000);
	}
	PointFinder::send_click(quit_point, hd);
	Sleep(1500);
	QPoint conform_point(0, 0);
	while (!PointFinder::is_valid_pos(conform_point))
	{
		conform_point = PointFinder::find_pos(hd, QString("./assets/confirm.jpg"));
		Sleep(1000);
	}
	PointFinder::send_click(conform_point, hd);
	while (get_challenge_result() != ChallengeStatus::Failed)
		Sleep(1000);
	PointFinder::send_click(QPoint(620, 240), hd);
}

bool BreakBoder::is_broken(QRect& rect)
{
	QString broken_image_path("./assets/breakboder/break_success.jpg");
	QPoint broken_pos = PointFinder::find_pos(hd,  broken_image_path,rect);
	return PointFinder::is_valid_pos(broken_pos);
}

ChallengeStatus BreakBoder::get_challenge_result()
{
	QPoint failed_pos = PointFinder::find_pos(hd, QString("./assets/failed.jpg"));
	if (PointFinder::is_valid_pos(failed_pos))
	{
		return ChallengeStatus::Failed;
	}
	QPoint success_pos = PointFinder::find_pos(hd, QString("./assets/challenge_success.jpg"));
	if (PointFinder::is_valid_pos(success_pos))
	{
		return ChallengeStatus::Success;
	}
	return Challenging;
}

void BreakBoder::run()
{
	const int length = check_point.size();
	for ( int i = 0; ; i++)
	{
		// 跳过已经突破的
		//if (is_broken(check_point[i]))
		//{
		//	if (i == 8)
		//	{
		//		// 刷新挑战组
		//		i = 0;
		//		Sleep(1000);
		//	}
		//	continue;
		//}
		QString msg = QString::fromLocal8Bit("正在挑战第%1个").arg(QString::number(i));
		emit MessageSignal(msg);
		if (make_challenge_failed(check_point[i]))
		{
			// 故意挑战失败
			Sleep(4000);
			
			challenge(check_point[i]);	// 正式挑战，直到通过
			Sleep(4000);
			// 每三次的奖励
			QPoint success_pos = PointFinder::find_pos(hd, QString("./assets/challenge_success.jpg"));
			if (PointFinder::is_valid_pos(success_pos))
			{
				PointFinder::send_click(success_pos, hd);
			}
		}
		else
		{
			QString msg = QString::fromLocal8Bit("第%1个可能已经挑战过了，跳过").arg(QString::number(i));
			emit MessageSignal(msg);
		}

		if (i == 8)
		{
			// 刷新挑战组
			i = -1;
			Sleep(1000);
		}
	}
}
