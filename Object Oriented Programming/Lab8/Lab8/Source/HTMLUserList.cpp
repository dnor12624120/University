#include "HTMLUserList.h"
#include "Utility.h"
#include "Record.h"

#include <fstream>
#include <iostream>

template<typename Key, typename Object>
void HTMLUserList<Key, Object>::setFilepath(const std::string& filepath)
{
	try
	{
		if (getFileExtension(filepath) != "html")
		{
			throw std::exception("File is not .html!");
		}
	}
	catch (std::exception& exception)
	{
		throw exception;
	}
	UserList<Key, Object>::m_filepath = filepath;
}


template<typename Key, typename Object>
void HTMLUserList<Key, Object>::loadAll()
{
	if (!UserList<Key, Object>::m_filepath.empty())
	{
		std::ifstream dataFile(UserList<Key, Object>::m_filepath);
		std::string line;
		for (int i = 0; i < 14; i++)
		{
			std::getline(dataFile, line);
		}
		std::getline(dataFile, line);
		while (line == "<tr>")
		{
			std::string title;
			std::string location;
			std::string timeOfCreation;
			std::string accessTime;
			std::string preview;
			//title
			std::getline(dataFile, title);
			title.erase(0, 4);
			title.erase(title.length() - 5, 5);
			//location
			std::getline(dataFile, location);
			location.erase(0, 4);
			location.erase(location.length() - 5, 5);
			//time of creation
			std::getline(dataFile, timeOfCreation);
			timeOfCreation.erase(0, 4);
			timeOfCreation.erase(timeOfCreation.length() - 5, 5);
			//access time
			std::getline(dataFile, accessTime);
			accessTime.erase(0, 4);
			accessTime.erase(accessTime.length() - 5, 5);
			//preview
			std::getline(dataFile, preview);
			preview.erase(0, 4);
			preview.erase(preview.length() - 5, 5);
			Record record(title, location, timeOfCreation, accessTime, preview);
			UserList<Key, Object>::m_list[title] = record;
			std::getline(dataFile, line);
			std::getline(dataFile, line);
		}
		dataFile.close();
	}
}

template<typename Key, typename Object>
void HTMLUserList<Key, Object>::addObject(const Key& key, const Object& object)
{
	if (!UserList<Key, Object>::m_filepath.empty())
	{
		std::ofstream dataFile(UserList<Key, Object>::m_filepath, std::ios::trunc);
		dataFile << "<!DOCTYPE html>" << '\n';
		dataFile << "<html>" << '\n';
		dataFile << "<head>" << '\n';
		dataFile << "<title>Record list</title>" << '\n';
		dataFile << "</title>" << '\n';
		dataFile << "<body>" << '\n';
		dataFile << "<table border=\"1\">" << '\n';
		dataFile << "<tr>" << '\n';
		dataFile << "<td>Title</td>" << '\n';
		dataFile << "<td>Location</td>" << '\n';
		dataFile << "<td>Time Of Creation</td>" << '\n';
		dataFile << "<td>Access Times</td>" << '\n';
		dataFile << "<td>Footage Preview</td>" << '\n';
		dataFile << "</tr>" << '\n';
		for (auto record = UserList<Key, Object>::m_list.begin(); record != UserList<Key, Object>::m_list.end(); record++)
		{
			dataFile << "<tr>" << '\n';
			dataFile << "<td>" << record->second.getTitle() << "</td>" << '\n';
			dataFile << "<td>" << record->second.getLocation() << "</td>" << '\n';
			dataFile << "<td>" << record->second.getTimeOfCreation() << "</td>" << '\n';
			dataFile << "<td>" << record->second.getTimeAccessed() << "</td>" << '\n';
			dataFile << "<td>" << record->second.getFootagePreview() << "</td>" << '\n';
			dataFile << "</tr>" << '\n';
		}
		UserList<Key, Object>::m_list[key] = object;
		dataFile << "<tr>" << '\n';
		dataFile << "<td>" << object.getTitle() << "</td>" << '\n';
		dataFile << "<td>" << object.getLocation() << "</td>" << '\n';
		dataFile << "<td>" << object.getTimeOfCreation() << "</td>" << '\n';
		dataFile << "<td>" << object.getTimeAccessed() << "</td>" << '\n';
		dataFile << "<td>" << object.getFootagePreview() << "</td>" << '\n';
		dataFile << "</tr>" << '\n';
		dataFile << "</table>" << '\n';
		dataFile << "</body>" << '\n';
		dataFile << "</html>" << '\n';
		dataFile.close();
	}
}

template class HTMLUserList<std::string, Record>;