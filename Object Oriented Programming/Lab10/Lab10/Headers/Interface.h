#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Interface.h"
#include "ui_UserList.h"
#include "InputValidator.h"
#include "qwindow.h"
#include "qlistwidget.h"
#include "qlabel.h"

#include <memory>

class Controller;

enum InterfaceAccess
{
	ADMIN,
	USER
};

class Interface : public QMainWindow
{
	public:
		Interface(std::unique_ptr<Controller> controller, QWidget *parent = Q_NULLPTR);
		~Interface();

	private:
		void setupUserList();
		void loadFromRepository();
		void loadAdminList();
		void loadUserList();
		void setConnections();
		void addRecord();
		void updateRecord();
		void deleteRecord();
		void setAdminListFilepath();
		void setUserListFilepath();
		void showUserList();
		void showAdminList();
		void addToUserList();
		void addToAdminList();
		void setCurrentUser();
		void openAdminList();
		void filter();
		void next();
		void userNext();
		void undoAdmin();
		void redoAdmin();
		void undoUser();
		void redoUser();

		InputValidator m_validator;
		std::unique_ptr<Controller> m_controller;
		Ui::InterfaceClass ui;
		QListWidget* m_filterList;
		QListWidget* m_adminList;
		QListWidget* m_userList;

	Q_OBJECT
};


