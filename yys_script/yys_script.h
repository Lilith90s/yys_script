#pragma once

#include  <Windows.h>
#include <QtWidgets/QMainWindow>
#include "ui_yys_script.h"
//1����ʼ��Ҫ�ȶ��������
static HHOOK hook;

//2��װ���ӣ������Ǹĳɶ���һ������,�����������װ���Ӻ�����
static int set_mousehook();

//3����һ�����Ӻ���ָ��
// LRESULT CALLBACK mouseHook(int nCode, WPARAM wParam, LPARAM lParam);

//4ж�ع��ӣ�ͬ�����������
static void unload_mousehook();

class yys_script : public QMainWindow
{
	Q_OBJECT
public:
	yys_script(QWidget *parent = Q_NULLPTR);
	~yys_script();
private slots:
	/**
	 * \brief 
	 */
	void on_testButton_clicked();
	
private:

	void send_click(QPoint& pos);
	
	Ui::yys_scriptClass ui;

	HWND hd_;

	
};
