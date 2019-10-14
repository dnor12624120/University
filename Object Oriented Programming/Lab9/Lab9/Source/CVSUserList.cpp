#include "CVSUserList.h"
#include "Utility.h"
#include "Record.h"

#include <fstream>

template<typename Key, typename Object>
void CVSUserList<Key, Object>::setFilepath(const std::string& filepath)
{
	try
	{
		if (getFileExtension(filepath) != "csv")
		{
			throw std::exception("File is not .csv!");
		}
	}
	catch (std::exception& exception)
	{
		throw exception;
	}
	UserList<Key, Object>::m_filepath = filepath;
	std::ifstream dataFile;
	dataFile.open(UserList<Key, Object>::m_filepath, std::ios::out);
	dataFile.close();
}


template<typename Key, typename Object>
void CVSUserList<Key, Object>::loadAll()
{
	if (!UserList<Key, Object>::m_filepath.empty())
	{
		bool canRead = true;
		std::ifstream dataFile(UserList<Key, Object>::m_filepath);
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
				Record record;
				dataFile >> record;
				UserList<Key, Object>::m_list[record.getTitle()] = record;
			}
			catch (std::exception& exception)
			{

			}
		}
		dataFile.close();
	}
}

template<typename Key, typename Object>
void CVSUserList<Key, Object>::addObject(const Key& key, const Object& object)
{
	if (!UserList<Key, Object>::m_filepath.empty())
	{
		std::ofstream dataFile(UserList<Key, Object>::m_filepath, std::ios::app);
		dataFile << object << '\n';
		UserList<Key, Object>::m_list[key] = object;
		dataFile.close();
	}
}

template class CVSUserList<std::string, Record>;