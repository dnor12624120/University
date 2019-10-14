#include "Repository.h"
#include "Record.h"
#include "Utility.h"

#include <exception>
#include <iostream>

void Repository::addElement(const std::string& title, std::unique_ptr<Record> record)
{
	if (m_elements.find(title) != m_elements.end())
	{
		throw std::exception("Record already exists in repository!\n");
	}
	m_elements.insert(std::make_pair(title, std::move(record)));
}

void Repository::removeElement(const std::string& title)
{
	if (m_elements.find(title) == m_elements.end())
	{
		throw std::exception("No record with given key exists!\n");
	}
	m_elements.erase(title);
}

void Repository::updateElement(const std::string& title, const std::string& newTitle, std::unique_ptr<Record> newRecord)
{
	if (m_elements.find(title) == m_elements.end())
	{
		throw std::exception("No record with given key exists!\n");
	}
	if (m_elements.find(newTitle) != m_elements.end())
	{
		throw std::exception("Record already exists in repository!\n");
	}
	m_elements.erase(title);
	m_elements.insert(std::make_pair(newTitle, std::move(newRecord)));
}

Record Repository::getRecord(const std::string& title)
{
	if (m_elements.find(title) == m_elements.end())
	{
		throw std::exception("No record with given key exists!");
	}
	return Record(m_elements[title].get());
}

std::map<std::string, std::unique_ptr<Record>>::iterator Repository::iterator()
{
	return std::map<std::string, std::unique_ptr<Record>>::iterator();
}

std::map<std::string, std::unique_ptr<Record>>::iterator Repository::begin()
{
	return m_elements.begin();
}

std::map<std::string, std::unique_ptr<Record>>::iterator Repository::end()
{
	return m_elements.end();
}

std::map<std::string, Record> Repository::filterTimesAccessed(const std::string& location, const std::string& timesAccessed)
{
	std::map<std::string, Record> filteredRecords;
	for (auto record  = m_elements.begin(); record != m_elements.end(); record++)
	{
		if(record->second->getLocation() == location && convertStringToInt(record->second->getTimeAccessed()) < 
		   convertStringToInt(timesAccessed))
		{
			filteredRecords.insert(std::make_pair(record->second->getTitle(), Record(record->second.get())));
		}
	}
	return filteredRecords;
}