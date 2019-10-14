#pragma once

#include "CVSRepository.h"
#include "Record.h"
#include "Exception.h"

#include <memory>
#include <fstream>
#include <filesystem>

template<typename Key, typename Object>
CVSRepository<Key, Object>::CVSRepository()
{

}

template<typename Key, typename Object>
CVSRepository<Key, Object>::CVSRepository(const std::string& filepath) :
	Repository<Key, Object>(),
	m_filepath(filepath)
{

}

template<typename Key, typename Object>
void CVSRepository<Key, Object>::setFilepath(const std::string& filepath)
{
	m_filepath = filepath;
	Repository<Key, Object>::clear();
}

template<typename Key, typename Object>
void CVSRepository<Key, Object>::loadObjects()
{
	if (!m_filepath.empty())
	{
		bool canRead = true;
		std::ifstream dataFile(m_filepath);
		if (dataFile.peek() == std::ifstream::traits_type::eof())
		{
			canRead = false;
		}
		while (canRead)
		{
			if (dataFile.eof())
			{
				canRead = false;
			}
			try
			{
				Record* record = new Record();
				dataFile >> *record;
				std::unique_ptr<Record> recordPointer(record);
				Repository<Key, Object>::addObject(record->getTitle(), std::move(recordPointer));
			}
			catch (std::exception& exception)
			{

			}
		}
		dataFile.close();
	}
}

template<typename Key, typename Object>
void CVSRepository<Key, Object>::addObject(const Key& key, std::unique_ptr<Object> object)
{
	if (!m_filepath.empty())
	{
		std::ofstream dataFile(m_filepath, std::ios::app);
		dataFile << *(object.get()) << '\n';
		Repository<Key, Object>::addObject(key, std::move(object));
		dataFile.close();
	}
}

template<typename Key, typename Object>
void CVSRepository<Key, Object>::removeObject(const Key& key)
{
	if (!m_filepath.empty())
	{
		Repository<Key, Object>::removeObject(key);
		std::ofstream dataFile(m_filepath, std::ios::trunc);
		dataFile.close();
		dataFile = std::ofstream(m_filepath, std::ios::out);
		for (auto object = Repository<Key, Object>::m_elements.begin(); object != Repository<Key, Object>::m_elements.end(); object++)
		{
			dataFile << *(object->second.get()) << '\n';
		}
		dataFile.close();
	}
}
template class CVSRepository<std::string, Record>;