#include "yys_script.h"
#include <Windows.h>
#include <QListWidget>
#include <string>
#include <QDebug>
#include <QScreen>
#include <QScrollBar>
#include "PointFinder.h"

LRESULT mouseHook(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (wParam == WM_XBUTTONDOWN)
	{
		qDebug() << wParam;
	}
	else if (wParam == WM_XBUTTONUP)
	{
		qDebug() << wParam;
	}else if (wParam == MK_CONTROL)
	{
		qDebug() << wParam;
	}
	qDebug() << wParam;
	return CallNextHookEx(0, nCode, wParam, lParam);
}

int set_mousehook()
{
	hook = SetWindowsHookExW(WH_KEYBOARD_LL, mouseHook, GetModuleHandle(0), NULL);
	return 0;
}

void unload_mousehook()
{
	UnhookWindowsHookEx(hook);
}

/**
 * \brief 
 * \param parent 
 */
yys_script::yys_script(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	// set_mousehook();
	wchar_t* title = L"����ʦ-������Ϸ";
	hd_ = FindWindow(nullptr, title);
	char title1[50];
	int pid = GetProcessId(hd_);
	GetWindowTextA(hd_, title1, 50);
	GetProcessId(hd_);
	if (hd_)
	{
		ui.logWidget->addItem(QString::fromLocal8Bit("��ȡ") + QString::fromLocal8Bit(title1) + QString::fromLocal8Bit("�ɹ�:") + QString::number(pid));
		fsm_ = new FSM(hd_);
		connect(fsm_,&FSM::MessageSignal,[this](QString &msg)
		{
			this->ui.logWidget->addItem(msg);
			ui.logWidget->verticalScrollBar()->setValue(99);
		});
	}
	else
	{
		ui.logWidget->addItem(QString::fromLocal8Bit("��ȡ���ھ���쳣!����ʦδ������"));
	}
	RECT yys_rect;
	GetWindowRect(hd_, &yys_rect);
	auto pos = PointFinder::get_chest_pos(hd_);
}

yys_script::~yys_script()  // NOLINT(hicpp-use-equals-default)
{
	// unload_mousehook();
	delete fsm_, fsm_ = nullptr;
}

void yys_script::run()
{
	fsm_->start();
}

void yys_script::on_ExploreButton_clicked() const
{																								
	fsm_->SetTransition(transition::Transition::EXPLORE);
}

void yys_script::on_screenShotsButton_clicked() const
{
	auto screen = QGuiApplication::primaryScreen();
	const auto map = screen->grabWindow(reinterpret_cast<WId>(hd_)/*,578,122,41,39*/);
	map.save("shots.jpg", "JPG");
}




