#include "Controller.h"
#include "Record.h"
#include "Interface.h"
#include "CVSRepository.h"

#include <iostream>

Controller::Controller(std::unique_ptr<Repository<std::string, Record>> repository):
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
			m_userListIterator = m_repository->begin();
			m_adminListIterator = m_repository->begin();
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
	return m_currentUser == InterfaceAccess::ADMIN ?
	 m_adminListIterator : m_userListIterator;
}

void Controller::incrementListIterator()
{
	if (m_currentUser == InterfaceAccess::ADMIN)
	{
		m_adminListIterator++;
		if (m_adminListIterator == m_repository->end())
		{
			m_adminListIterator = m_repository->begin();
		}
	}
	else
	{
		m_userListIterator++;
		if (m_userListIterator == m_repository->end())
		{
			m_userListIterator = m_repository->begin();
		}
	}
}

void Controller::saveRecord(const Record& record)
{
	m_currentUser == InterfaceAccess::ADMIN ? 
		m_adminList.insert(std::make_pair(record.getTitle(), record)) : m_userList.insert(std::make_pair(record.getTitle(), record));
}


std::map<std::string, Record>::iterator Controller::userListIterator()
{
	return std::map<std::string, Record>::iterator();
}

std::map<std::string, Record>::iterator Controller::userListBegin()
{
	return m_currentUser == InterfaceAccess::ADMIN ? m_adminList.begin() : m_userList.begin();
}


std::map<std::string, Record>::iterator Controller::userListEnd()
{
	return m_currentUser == InterfaceAccess::ADMIN ? m_adminList.end() : m_userList.end();
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
}