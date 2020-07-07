#pragma once
#include <qthread.h>
#include <qvector.h>
#include <QPoint>
#include <QColor>
#include <Windows.h>
#include <QString>

enum ChallengeStatus
{
	Success,
	Failed,
	Challenging
};
struct StateColor
{
	static QColor color_default; // 初始的颜色
	static QColor color_success; // 挑战成功的颜色
	static QColor color_failed;	// 挑战失败的颜色
};
/*检查点*/
struct CheckPoint
{
	QPoint is_success_point; // 检查是否成功的点
	QPoint is_failed_point;	// 检查是否失败的点
};
class BreakBoder :
	public QThread
{
	Q_OBJECT

public:

	BreakBoder(HWND hd);

	bool make_challenge_failed(QRect &rect);

	void challenge(QRect &rect);

signals:
	void MessageSignal(QString msg);

private:
	void challenge_action(QRect &rect);

	bool attack_action();

	void quit_attack_action();

	bool is_broken(QRect &rect);

	// 获取挑战结果
	ChallengeStatus get_challenge_result();
public:
	void run() override;
private:
	QVector<QRect> check_point;

	HWND hd;
};

