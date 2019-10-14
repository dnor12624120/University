#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AdminInterface.h"
#include "Controller.h"

#include <string>
#include <memory>

class QLabel;
class QLineEdit;
class QPushButton;
class QListWidget;

class AdminInterface : public QMainWindow
{
	public:
		AdminInterface(QWidget *parent = Q_NULLPTR);
		~AdminInterface();

		void setController(std::unique_ptr<Controller> controller);
		void loadList();

	private:
		void setup();
		void addLabel(QLabel* label, const std::string& name, int x, int y, int width, int height);
		void addLineEdit(QLineEdit* lineEdit, int x, int y, int width, int height);
		void addPushButton(QPushButton* button, const std::string& name, int x, int y, int width, int height);
		void addListWidget(QListWidget* list, int x, int y, int width, int height);

		std::unique_ptr<Controller> m_controller;
		Ui::AdminInterfaceClass ui;
		QLabel* m_enterRecord;
		QLabel* m_title;
		QLabel* m_location;
		QLabel* m_timeOfCreation;
		QLabel* m_accessTime;
		QLabel* m_footagePreview;
		QLabel* m_filterLocation;
		QLabel* m_filterAccessTime;
		QLineEdit* m_titleLine;
		QLineEdit* m_locationLine;
		QLineEdit* m_timeOfCreationLine;
		QLineEdit* m_accessTimeLine;
		QLineEdit* m_footagePreviewLine;
		QLineEdit* m_filterLocationLine;
		QLineEdit* m_filterAccessTimeLine;
		QPushButton* m_addRecord;
		QPushButton* m_updateRecord;
		QPushButton* m_deleteRecord;
		QPushButton* m_filter;
		QPushButton* m_addList;
		QPushButton* m_viewList;
		QListWidget* m_list;
		QListWidget* m_myList;
	Q_OBJECT
};
