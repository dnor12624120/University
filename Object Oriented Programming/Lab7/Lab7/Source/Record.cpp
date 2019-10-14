#include "Record.h"

#include <iostream>
#include <sstream>
#include <vector>

Record::Record(const std::string& title, const std::string& location, const std::string& timeOfCreation,
			   const std::string& timeAccessed, const std::string& footagePreview):
	m_title(title),
	m_location(location),
	m_timeOfCreation(timeOfCreation),
	m_timeAccessed(timeAccessed),
	m_footagePreview(footagePreview)
{

}

Record::Record(Record* record) :
	m_title(record->m_title),
	m_location(record->m_location),
	m_timeOfCreation(record->m_timeOfCreation),
	m_timeAccessed(record->m_timeAccessed),
	m_footagePreview(record->m_footagePreview)
{

}

void Record::setTitle(const std::string& title)
{
	m_title = title;
}

void Record::setLocation(const std::string& location)
{
	m_location = location;
}

void Record::setTimeOfCreation(const std::string& timeOfCreation)
{
	m_timeOfCreation = timeOfCreation;
}

void Record::setTimeAccessed(const std::string& timeAccessed)
{
	m_timeAccessed = timeAccessed;
}

void Record::setFootagePreview(const std::string& footagePreview)
{
	m_footagePreview = footagePreview;
}

std::istream& operator>>(std::istream& inputStream, Record& record)
{
	std::string recordData;
	std::string recordField;
	std::stringstream stringstream;
	std::vector<std::string> recordFields;
	std::getline(inputStream, recordData);
	stringstream << recordData;
	while (std::getline(stringstream, recordField, ','))
	{
		recordFields.emplace_back(recordField);
	}
	if (!recordFields.size())
	{
		throw std::exception("Error reading record data!");
	}
	record.m_title = recordFields[0];
	record.m_location = recordFields[1];
	record.m_timeOfCreation = recordFields[2];
	record.m_timeAccessed = recordFields[3];
	record.m_footagePreview = recordFields[4];
	return inputStream;
}

std::ostream& operator<<(std::ostream& outputStream, const Record& record)
{
	outputStream << record.m_title << ',' << record.m_location << ',' <<
		record.m_timeOfCreation << ',' << record.m_timeAccessed << ',' << record.m_footagePreview;
	return outputStream;
}