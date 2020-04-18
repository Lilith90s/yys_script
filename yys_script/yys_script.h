#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_yys_script.h"

class yys_script : public QMainWindow
{
	Q_OBJECT

public:
	yys_script(QWidget *parent = Q_NULLPTR);

private:
	Ui::yys_scriptClass ui;
};
