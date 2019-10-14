#include "Controller.h"
#include "Record.h"
#include "CVSRepository.h"
#include "UserList.h"
#include "CVSUserList.h"
#include "HTMLUserList.h"
#include "Utility.h"

#include <iostream>

enum InterfaceAccess
{
	ADMIN,
	USER
};

Controller::Controller(std::unique_ptr<Repository<std::string, Record>> repository) :
	m_repository(std::move(repository)),
	m_currentUser(InterfaceAccess::USER)
{

}

void Controller::addRecord(const std::string& title, const std::string& location, const std::string& timeOfCreation,
						   const std::string& timeAccessed, const std::string& footagePreview)
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
}

void Controller::updateRecord(const std::string& title, const std::string& newLocation,
							  const std::string& newTimeOfCreation, const std::string& newTimeAccessed,
							  const std::string& newFootagePreview)
{
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
}

void Controller::deleteRecord(const std::string& title)
{
	try
	{
		m_repository->removeObject(title);
	}
	catch (std::exception& exception)
	{
		throw exception;
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