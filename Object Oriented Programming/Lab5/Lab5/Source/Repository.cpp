#include "Repository.h"
#include "Record.h"

#include <exception>


void Repository::addElement(const std::string& key, std::unique_ptr<Record> element)
{
	if (m_elements.find(key) != m_elements.end())
	{
		throw std::exception("Record already exists in repository!\n");
	}
	m_elements.insert(std::make_pair(key, std::move(element)));
}

void Repository::removeElement(const std::string& key)
{
	if (m_elements.find(key) == m_elements.end())
	{
		throw std::exception("No record with given key exists!\n");
	}
	m_elements.erase(key);
}

void Repository::updateElement(const std::string& key, const std::string& newKey, std::unique_ptr<Record> newElement)
{
	if (m_elements.find(key) == m_elements.end())
	{
		throw std::exception("No record with given key exists!\n");
	}
	if (m_elements.find(newKey) != m_elements.end())
	{
		throw std::exception("Record already exists in repository!\n");
	}
	m_elements.erase(key);
	m_elements.insert(std::make_pair(newKey, std::move(newElement)));
}

Record* Repository::getRecord(const std::string& key)
{
	if (m_elements.find(key) == m_elements.end())
	{
		throw std::exception("No record with given key exists!\n");
	}
	return m_elements[key].get();
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