#include "Controller.h"
#include "Record.h"
#include "CVSRepository.h"
#include "UserList.h"
#include "CVSUserList.h"
#include "HTMLUserList.h"
#include "Utility.h"
#include "Operation.h"

#include <iostream>

enum InterfaceAccess
{
	ADMIN,
	USER
};

Controller::Controller(std::unique_ptr<Repository<std::string, Record>> repository,
					   std::unique_ptr<FunctionStack> userStack,
					   std::unique_ptr<FunctionStack> adminStack) :
	m_repository(std::move(repository)),
	m_currentUser(InterfaceAccess::USER),
	m_userStack(std::move(userStack)),
	m_adminStack(std::move(adminStack))
{

}

void Controller::addRecord(const std::string& title, const std::string& location, const std::string& timeOfCreation,
						   const std::string& timeAccessed, const std::string& footagePreview, bool add)
{
	try
	{
		std::unique_ptr<Record> record = std::unique_ptr<Record>(new Record(title, location, timeOfCreation, timeAccessed, footagePreview));
		m_repository->addObject(title, std::move(record));
		if (m_repository->size() == 1)
		{
			m_userIterator = m_repository->begin();
			m_adminIterator = m_repository->begin();
		}
	}
	catch (std::exception& exception)
	{
		throw exception;
	}
	if (add)
	{
		Record r = m_repository->getObject(title);
		std::function<void()> redo = std::bind(&Controller::addRecord, this, r.getTitle(), r.getLocation(), r.getTimeOfCreation(),
											   r.getTimeAccessed(), r.getFootagePreview(), false);
		std::function<void()> undo = std::bind(&Controller::deleteRecord, this, r.getTitle(), false);
		Operation operation(undo, redo);
		m_adminStack->push(operation);
	}
}

void Controller::updateRecord(const std::string& title, const std::string& newLocation,
							  const std::string& newTimeOfCreation, const std::string& newTimeAccessed,
							  const std::string& newFootagePreview, bool add)
{
	Record r = m_repository->getObject(title);
	try
	{
		m_repository->removeObject(title);
		std::unique_ptr<Record> newRecord = std::unique_ptr<Record>(new Record(title, newLocation,
																			   newTimeOfCreation, newTimeAccessed, newFootagePreview));
		m_repository->addObject(title, std::move(newRecord));
	}
	catch (std::exception& exception)
	{
		throw exception;
	}
	if (add)
	{
		if (add)
		{
			std::function<void()> undo = std::bind(&Controller::updateRecord, this, r.getTitle(), r.getLocation(), r.getTimeOfCreation(),
												   r.getTimeAccessed(), r.getFootagePreview(), false);
			std::function<void()> redo = std::bind(&Controller::updateRecord, this, r.getTitle(), newLocation,
												   newTimeOfCreation, newTimeAccessed, newFootagePreview, false);
			Operation operation(undo, redo);
			m_adminStack->push(operation);
		}
	}
}

void Controller::deleteRecord(const std::string& title, bool add)
{
	Record r = m_repository->getObject(title);
	try
	{
		m_repository->removeObject(title);
	}
	catch (std::exception& exception)
	{
		throw exception;
	}
	if (add)
	{
		std::function<void()> undo = std::bind(&Controller::addRecord, this, r.getTitle(), r.getLocation(), r.getTimeOfCreation(),
											   r.getTimeAccessed(), r.getFootagePreview(), false);
		std::function<void()> redo = std::bind(&Controller::deleteRecord, this, r.getTitle(), false);
		Operation operation(undo, redo);
		m_adminStack->push(operation);
	}
}

Record Controller::getRecord(const std::string& title) const
{
	return m_repository->getObject(title);
}

std::map<std::string, std::unique_ptr<Record>>::iterator Controller::iterator()
{
	return m_repository->iterator();
}

std::map<std::string, std::unique_ptr<Record>>::iterator Controller::begin()
{
	return m_repository->begin();
}

std::map<std::string, std::unique_ptr<Record>>::iterator Controller::end()
{
	return m_repository->end();
}

std::map<std::string, std::unique_ptr<Record>>::iterator Controller::getListIterator()
{
	return m_currentUser == InterfaceAccess::ADMIN ? m_adminIterator : m_userIterator;
}

void Controller::incrementListIterator()
{
	if (m_currentUser == InterfaceAccess::ADMIN)
	{
		m_adminIterator++;
		if (m_adminIterator == m_repository->end())
		{
			m_adminIterator = m_repository->begin();
		}
	}
	else
	{
		m_userIterator++;
		if (m_userIterator == m_repository->end())
		{
			m_userIterator = m_repository->begin();
		}
	}
}

void Controller::saveRecord(const Record& record)
{
	m_currentUser == InterfaceAccess::ADMIN ?
		m_adminList->addObject(record.getTitle(), record) : m_userList->addObject(record.getTitle(), record);
}


std::vector<Record> Controller::filter(std::function<bool(Record*)> filterFunction)
{
	return m_repository->filter(filterFunction);
}

void Controller::setUser(InterfaceAccess access)
{
	m_currentUser = access;
}

void Controller::setFilepath(const std::string& filepath)
{
	dynamic_cast<CVSRepository<std::string, Record>*>(m_repository.get())->setFilepath(filepath);
}

void Controller::loadRecords()
{
	dynamic_cast<CVSRepository<std::string, Record>*>(m_repository.get())->loadObjects();
	m_userIterator = m_repository->begin();
	m_adminIterator = m_repository->begin();
}

std::map<std::string, Record>::iterator Controller::userListBegin()
{
	return m_userList->begin();
}

std::map<std::string, Record>::iterator Controller::userListEnd()
{
	return m_userList->end();
}

std::map<std::string, Record>::iterator Controller::adminListBegin()
{
	return m_adminList->begin();
}

std::map<std::string, Record>::iterator Controller::adminListEnd()
{
	return m_adminList->end();
}

void Controller::setUserListFilepath(const std::string& filepath)
{
	getFileExtension(filepath) == "csv" ? m_userList = std::unique_ptr<UserList<std::string, Record>>(new CVSUserList<std::string, Record>()) :
		m_userList = std::unique_ptr<UserList<std::string, Record>>(new HTMLUserList<std::string, Record>());
	m_userList->setFilepath(filepath);
}

void Controller::setAdminListFilepath(const std::string& filepath)
{
	getFileExtension(filepath) == "csv" ? m_adminList = std::unique_ptr<UserList<std::string, Record>>(new CVSUserList<std::string, Record>()) :
		m_adminList = std::unique_ptr<UserList<std::string, Record>>(new HTMLUserList<std::string, Record>());
	m_adminList->setFilepath(filepath);
}

void Controller::loadUserListObjects()
{
	m_userList->loadAll();
}

void Controller::loadAdminListObjects()
{
	m_adminList->loadAll();
}

void Controller::openUserList()
{
	std::string command;
	std::string filepath;
	if (m_currentUser == InterfaceAccess::ADMIN)
	{
		filepath = m_adminList->getFilepath();
	}
	else
	{
		filepath = m_userList->getFilepath();
	}
	for (int i = 0; i < filepath.length(); i++)
	{
		if (filepath[i] == ' ')
		{
			filepath.insert(i, "\"");
			filepath.insert(i + 2, "\"");
			i += 2;
		}
	}
	command = std::string("start " + filepath);
	system(command.c_str());
}