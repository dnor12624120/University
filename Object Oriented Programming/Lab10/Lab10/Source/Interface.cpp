#include "Interface.h"
#include "Controller.h"
#include "Record.h"
#include "FilterFunctions.h"

#include <sstream>
#include <functional>
#include <iostream>
#include "qmessagebox.h"

Interface::Interface(std::unique_ptr<Controller> controller, QWidget *parent):
	m_controller(std::move(controller)),
	QMainWindow(parent)
{
	ui.setupUi(this);
	loadFromRepository();
	setupUserList();
	setConnections();
}

Interface::~Interface()
{
	delete m_userList;
}

void Interface::setupUserList()
{
	m_adminList = new QListWidget;
	m_userList = new QListWidget;
	m_filterList = new QListWidget;
}

void Interface::setConnections()
{
	connect(ui.add_record, &QPushButton::clicked, this, &Interface::addRecord);
	connect(ui.update_record, &QPushButton::clicked, this, &Interface::updateRecord);
	connect(ui.delete_record, &QPushButton::clicked, this, &Interface::deleteRecord);
	connect(ui.view_list, &QPushButton::clicked, this, &Interface::showAdminList);
	connect(ui.set_filepath, &QPushButton::clicked, this, &Interface::setAdminListFilepath);
	connect(ui.add_to_list, &QPushButton::clicked, this, &Interface::addToAdminList);
	connect(ui.tab, &QTabWidget::currentChanged, this, &Interface::setCurrentUser);
	connect(ui.open_list, &QPushButton::clicked, this, &Interface::openAdminList);
	connect(ui.filter, &QPushButton::clicked, this, &Interface::filter);
	connect(ui.view_list_user, &QPushButton::clicked, this, &Interface::showUserList);
	connect(ui.set_filepath_user, &QPushButton::clicked, this, &Interface::setUserListFilepath);
	connect(ui.add_to_list_user, &QPushButton::clicked, this, &Interface::addToUserList);
	connect(ui.open_list_user, &QPushButton::clicked, this, &Interface::openAdminList);
	connect(ui.next, &QPushButton::clicked, this, &Interface::next);
	connect(ui.next_user, &QPushButton::clicked, this, &Interface::userNext);
	connect(ui.undo, &QPushButton::clicked, this, &Interface::undoAdmin);
	connect(ui.redo, &QPushButton::clicked, this, &Interface::redoAdmin);
	connect(ui.undo_user, &QPushButton::clicked, this, &Interface::undoUser);
	connect(ui.undo_user, &QPushButton::clicked, this, &Interface::redoUser);
}

void Interface::loadFromRepository()
{
	ui.list->clear();
	ui.list_user->clear();
	for (auto record = m_controller->begin(); record != m_controller->end(); record++)
	{
		std::stringstream recordString;
		recordString << *(record->second.get());
		ui.list->addItem(recordString.str().c_str());
		ui.list_user->addItem(recordString.str().c_str());
	}
}

void Interface::loadAdminList()
{
	m_adminList->clear();
	for (auto record = m_controller->adminListBegin(); record != m_controller->adminListEnd(); record++)
	{
		std::stringstream recordString;
		recordString << record->second;
		m_adminList->addItem(recordString.str().c_str());
	}
}

void Interface::loadUserList()
{
	m_userList->clear();
	for (auto record = m_controller->userListBegin(); record != m_controller->userListEnd(); record++)
	{
		std::stringstream recordString;
		recordString << record->second;
		m_userList->addItem(recordString.str().c_str());
	}
}

void Interface::addRecord()
{
	std::string title = ui.title_edit->text().toUtf8().constData();
	std::string location = ui.location_edit->text().toUtf8().constData();	
	std::string timeOfCreation = ui.toc_edit->text().toUtf8().constData();
	std::string accessTime = ui.at_edit->text().toUtf8().constData();
	std::string footagePreview = ui.fp_edit->text().toUtf8().constData();
	try
	{
		m_validator.validateTitle(title);
		m_validator.validateLocation(location);
		m_validator.validateTimeOfCreation(timeOfCreation);
		m_validator.validateAccessTime(accessTime);
		m_validator.validateFootagePreview(footagePreview);
		m_controller->addRecord(title, location, timeOfCreation, accessTime, footagePreview, true);
		loadFromRepository();
	}
	catch (std::exception& exception)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", exception.what());
		messageBox.setFixedSize(500, 200);
	}
	ui.title_edit->setText(QString(""));
	ui.location_edit->setText(QString(""));
	ui.toc_edit->setText(QString(""));
	ui.at_edit->setText(QString(""));
	ui.fp_edit->setText(QString(""));
}

void Interface::updateRecord()
{
	std::string title = ui.title_edit->text().toUtf8().constData();
	std::string location = ui.location_edit->text().toUtf8().constData();
	std::string timeOfCreation = ui.toc_edit->text().toUtf8().constData();
	std::string accessTime = ui.at_edit->text().toUtf8().constData();
	std::string footagePreview = ui.fp_edit->text().toUtf8().constData();
	try
	{
		m_validator.validateTitle(title);
		m_validator.validateLocation(location);
		m_validator.validateTimeOfCreation(timeOfCreation);
		m_validator.validateAccessTime(accessTime);
		m_validator.validateFootagePreview(footagePreview);
		m_controller->updateRecord(title, location, timeOfCreation, accessTime, footagePreview, true);
		loadFromRepository();
	}
	catch (std::exception& exception)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", exception.what());
		messageBox.setFixedSize(500, 200);
	}
	ui.title_edit->setText(QString(""));
	ui.location_edit->setText(QString(""));
	ui.toc_edit->setText(QString(""));
	ui.at_edit->setText(QString(""));
	ui.fp_edit->setText(QString(""));
}

void Interface::deleteRecord()
{
	std::string title = ui.title_edit->text().toUtf8().constData();
	try
	{
		m_validator.validateTitle(title);
		m_controller->deleteRecord(title, true);
		loadFromRepository();
	}
	catch (std::exception& exception)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", exception.what());
		messageBox.setFixedSize(500, 200);
	}
	ui.title_edit->setText(QString(""));
	ui.location_edit->setText(QString(""));
	ui.toc_edit->setText(QString(""));
	ui.at_edit->setText(QString(""));
	ui.fp_edit->setText(QString(""));
}

void Interface::setAdminListFilepath()
{
	std::string filepath = ui.filepath_edit->text().toUtf8().constData();
	m_controller->setAdminListFilepath(filepath);
	m_controller->loadAdminListObjects();
}

void Interface::setUserListFilepath()
{
	std::string filepath = ui.filepath_edit_user->text().toUtf8().constData();
	m_controller->setUserListFilepath(filepath);
	m_controller->loadUserListObjects();
}

void Interface::showUserList()
{
	loadUserList();
	m_userList->show();
}

void Interface::showAdminList()
{
	loadAdminList();
	m_adminList->show();
}

void Interface::addToAdminList()
{
	int index = ui.list->currentRow();
	std::string record = ui.list->item(index)->text().toUtf8().constData();
	std::string title;
	std::string location;
	std::string timeOfCreation;
	std::string accessTime;
	std::string footagePreview;
	title = record.substr(0, record.find(","));
	record.erase(record.begin(), record.begin() + record.find(",") + 1);
	location = record.substr(0, record.find(","));
	record.erase(record.begin(), record.begin() + record.find(",") + 1);
	timeOfCreation = record.substr(0, record.find(","));
	record.erase(record.begin(), record.begin() + record.find(",") + 1);
	accessTime = record.substr(0, record.find(","));
	record.erase(record.begin(), record.begin() + record.find(",") + 1);
	footagePreview = record.substr(0, record.find(","));
	m_controller->saveRecord(Record(title, location, timeOfCreation, accessTime, footagePreview));
	loadAdminList();
}

void Interface::addToUserList()
{
	int index = ui.list_user->currentRow();
	std::string record = ui.list_user->item(index)->text().toUtf8().constData();
	std::string title;
	std::string location;
	std::string timeOfCreation;
	std::string accessTime;
	std::string footagePreview;
	title = record.substr(0, record.find(","));
	record.erase(record.begin(), record.begin() + record.find(",") + 1);
	location = record.substr(0, record.find(","));
	record.erase(record.begin(), record.begin() + record.find(",") + 1);
	timeOfCreation = record.substr(0, record.find(","));
	record.erase(record.begin(), record.begin() + record.find(",") + 1);
	accessTime = record.substr(0, record.find(","));
	record.erase(record.begin(), record.begin() + record.find(",") + 1);
	footagePreview = record.substr(0, record.find(","));
	m_controller->saveRecord(Record(title, location, timeOfCreation, accessTime, footagePreview));
	loadUserList();
}

void Interface::setCurrentUser()
{
	int index = ui.tab->currentIndex();
	if (index == 0)
	{
		m_controller->setUser(InterfaceAccess::ADMIN);
	}
	else
	{
		m_controller->setUser(InterfaceAccess::USER);
	}
}

void Interface::openAdminList()
{
	m_controller->openUserList();
}

void Interface::filter()
{
	std::string location = ui.filter_location_edit->text().toUtf8().constData();
	std::string accessTime = ui.filter_at_edit->text().toUtf8().constData();
	try
	{
		m_filterList->clear();
		m_validator.validateLocation(location);
		m_validator.validateAccessTime(accessTime);
		auto filterFunction = std::bind(filterTimesAccessed, std::placeholders::_1, location, accessTime);
		auto records = m_controller->filter(filterFunction);
		for (auto record = records.begin(); record != records.end(); record++)
		{
			std::stringstream recordString;
			recordString << *record;
			m_filterList->addItem(recordString.str().c_str());
		}
		m_filterList->show();
	}
	catch (std::exception& exception)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", exception.what());
		messageBox.setFixedSize(500, 200);
	}
	ui.filter_location_edit->setText(QString(""));
	ui.filter_at_edit->setText(QString(""));
}

void Interface::next()
{
	if (ui.list->currentRow() == -1)
	{
		ui.list->setCurrentRow(0);
	}
	else if (ui.list->currentRow() == ui.list->count() - 1)
	{
		ui.list->setCurrentRow(0);
	}
	else
	{
		ui.list->setCurrentRow(ui.list->currentRow() + 1);
	}
}

void Interface::userNext()
{
	if (ui.list_user->currentRow() == -1)
	{
		ui.list_user->setCurrentRow(0);
	}
	else if (ui.list_user->currentRow() == ui.list_user->count() - 1)
	{
		ui.list_user->setCurrentRow(0);
	}
	else
	{
		ui.list_user->setCurrentRow(ui.list_user->currentRow() + 1);
	}
}

void Interface::undoAdmin()
{
	m_controller->undo();
	loadFromRepository();
}

void Interface::redoAdmin()
{
	m_controller->redo();
	loadFromRepository();
}

void Interface::undoUser()
{

}

void Interface::redoUser()
{

}