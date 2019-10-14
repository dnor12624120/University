#include "AdminInterface.h"
#include "qlabel.h"
#include "qlayout.h"
#include "qlineedit.h"
#include "qlistwidget.h"
#include "qpushbutton.h"
#include "Controller.h"


AdminInterface::AdminInterface(QWidget *parent) :
	QMainWindow(parent),
	m_enterRecord(new QLabel),
	m_title(new QLabel),
	m_location(new QLabel),
	m_timeOfCreation(new QLabel),
	m_accessTime(new QLabel),
	m_footagePreview(new QLabel),
	m_filterLocation(new QLabel),
	m_filterAccessTime(new QLabel),
	m_titleLine(new QLineEdit),
	m_locationLine(new QLineEdit),
	m_timeOfCreationLine(new QLineEdit),
	m_accessTimeLine(new QLineEdit),
	m_footagePreviewLine(new QLineEdit),
	m_filterLocationLine(new QLineEdit),
	m_filterAccessTimeLine(new QLineEdit),
	m_list(new QListWidget),
	m_addRecord(new QPushButton),
	m_updateRecord(new QPushButton),
	m_deleteRecord(new QPushButton),
	m_filter(new QPushButton),
	m_addList(new QPushButton),
	m_viewList(new QPushButton),
	m_myList(new QListWidget)
{
	ui.setupUi(this);
	setup();
}

AdminInterface::~AdminInterface()
{
	delete m_enterRecord;
	delete m_title;
	delete m_location;
	delete m_timeOfCreation;
	delete m_accessTime;
	delete m_footagePreview;
	delete m_titleLine;
	delete m_locationLine;
	delete m_timeOfCreationLine;
	delete m_accessTimeLine;
	delete m_footagePreviewLine;
	delete m_addRecord;
	delete m_list;
}

void AdminInterface::setController(std::unique_ptr<Controller> controller)
{
	m_controller = std::move(controller);
}

void AdminInterface::setup()
{
	setFixedSize(QSize(800, 500));
	addLabel(m_enterRecord, "Enter record", 10, 10, 100, 15);
	addLabel(m_title, "Title:", 10, 35, 100, 15);
	addLabel(m_location, "Location:", 10, 60, 100, 15);
	addLabel(m_timeOfCreation, "Time of creation:", 10, 85, 100, 15);
	addLabel(m_accessTime, "Access time:", 10, 110, 100, 15);
	addLabel(m_footagePreview, "Footage preview:", 10, 135, 100, 15);
	addLabel(m_filterLocation, "Location:", 10, 295, 100, 15);
	addLabel(m_filterAccessTime, "Access time:", 10, 320, 100, 15);
	addLineEdit(m_titleLine, 150, 35, 100, 20);
	addLineEdit(m_locationLine, 150, 60, 100, 20);
	addLineEdit(m_timeOfCreationLine, 150, 85, 100, 20);
	addLineEdit(m_accessTimeLine, 150, 110, 100, 20);
	addLineEdit(m_footagePreviewLine, 150, 135, 100, 20);
	addLineEdit(m_filterLocationLine, 150, 295, 100, 20);
	addLineEdit(m_filterAccessTimeLine, 150, 320, 100, 20);
	addPushButton(m_addRecord, "Add record", 90, 175, 100, 30);
	addPushButton(m_updateRecord, "Update record", 90, 210, 100, 30);
	addPushButton(m_deleteRecord, "Delete record", 90, 245, 100, 30);
	addPushButton(m_filter, "Filter", 90, 360, 100, 30);
	addPushButton(m_addList, "Add to list", 350, 340, 100, 30);
	addPushButton(m_viewList, "View list", 640, 340, 100, 30);
	addListWidget(m_list, 300, 10, 200, 300);
	addListWidget(m_myList, 590, 10, 200, 300);
}

void AdminInterface::loadList()
{
	for (auto record = m_controller->begin(); record != m_controller->end(); record++)
	{
		Record r(record->second.get());
		std::string str(r.getTitle() + ", " + r.getLocation() + ", " + r.getTimeOfCreation() + ", " + r.getTimeAccessed() + ", " + r.getFootagePreview());
		m_list->addItem(str.c_str());
	}
}

void AdminInterface::addLabel(QLabel* label, const std::string& name, int x, int y, int width, int height)
{
	label->setText(name.c_str());
	label->setGeometry(QRect(x, y, width, height));
	label->setParent(this);
}

void AdminInterface::addLineEdit(QLineEdit* lineEdit, int x, int y, int width, int height)
{
	lineEdit->setGeometry(QRect(x, y, width, height));
	lineEdit->setParent(this);
}

void AdminInterface::addPushButton(QPushButton* button, const std::string& name, int x, int y, int width, int height)
{
	button->setText(name.c_str());
	button->setGeometry(QRect(x, y, width, height));
	button->setParent(this);
}

void AdminInterface::addListWidget(QListWidget* list, int x, int y, int width, int height)
{
	list->setGeometry(QRect(x, y, width, height));
	list->setParent(this);
}