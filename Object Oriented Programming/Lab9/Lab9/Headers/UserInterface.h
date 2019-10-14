#pragma once

#include <QWidget>
#include "ui_UserInterface.h"

class UserInterface : public QWidget
{
	Q_OBJECT

public:
	UserInterface(QWidget *parent = Q_NULLPTR);
	~UserInterface();

private:
	Ui::UserInterface ui;
};
