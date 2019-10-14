#include "Repository.h"
#include "Record.h"
#include "Utility.h"
#include "Exception.h"

#include <exception>
#include <iostream>
#include <algorithm>

template<typename Key, typename Object>
void Repository<Key, Object>::addObject(const Key& key, std::unique_ptr<Object> object)
{
	if (m_elements.find(key) != m_elements.end())
	{
		throw RepositoryException("Object already exists in repository!\n");
	}
	m_elements.insert(std::make_pair(key, std::move(object)));
}

template<typename Key, typename Object>
void Repository<Key, Object>::removeObject(const Key& key)
{
	if (m_elements.find(key) == m_elements.end())
	{
		throw RepositoryException("No object with given key exists!\n");
	}
	m_elements.erase(key);
}

template<typename Key, typename Object>
Object Repository<Key, Object>::getObject(const Key& key)
{
	if (m_elements.find(key) == m_elements.end())
	{
		throw RepositoryException("No object with given key exists!");
	}
	return Record(m_elements[key].get());
}

template<typename Key, typename Object>
typename std::map<Key, std::unique_ptr<Object>>::iterator Repository<Key, Object>::iterator()
{
	return std::map<std::string, std::unique_ptr<Record>>::iterator();
}

template<typename Key, typename Object>
typename std::map<Key, std::unique_ptr<Object>>::iterator Repository<Key, Object>::begin()
{
	return m_elements.begin();
}

template<typename Key, typename Object>
typename std::map<Key, std::unique_ptr<Object>>::iterator Repository<Key, Object>::end()
{
	return m_elements.end();
}

template<typename Key, typename Object>
std::vector<Object> Repository<Key, Object>::filter(const std::function<bool(Object*)>& filterFunction)
{
	std::vector<Object> filteredRecords;

	std::for_each(m_elements.begin(), m_elements.end(),
				  [&filteredRecords, filterFunction](const auto& object)
	{
		if (filterFunction(object.second.get()))
		{
			filteredRecords.emplace_back(object.second.get());
		}
	});

	return filteredRecords;
}

template<typename Key, typename Object>
void Repository<Key, Object>::clear()
{
	m_elements.clear();
}

template class Repository<std::string, Record>;