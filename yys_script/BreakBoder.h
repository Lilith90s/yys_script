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
	static QColor color_default; // ��ʼ����ɫ
	static QColor color_success; // ��ս�ɹ�����ɫ
	static QColor color_failed;	// ��սʧ�ܵ���ɫ
};
/*����*/
struct CheckPoint
{
	QPoint is_success_point; // ����Ƿ�ɹ��ĵ�
	QPoint is_failed_point;	// ����Ƿ�ʧ�ܵĵ�
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

	// ��ȡ��ս���
	ChallengeStatus get_challenge_result();
public:
	void run() override;
private:
	QVector<QRect> check_point;

	HWND hd;
};

