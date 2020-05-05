#pragma once

#include  <Windows.h>
#include <QtWidgets/QMainWindow>
#include "ui_yys_script.h"
//1，开始都要先定义个钩子
static HHOOK hook;

//2安装钩子，这里是改成定义一个函数,函数里包含安装钩子函数；
static int set_mousehook();

//3定义一个钩子函数指针
// LRESULT CALLBACK mouseHook(int nCode, WPARAM wParam, LPARAM lParam);

//4卸载钩子，同样定义个函数
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
