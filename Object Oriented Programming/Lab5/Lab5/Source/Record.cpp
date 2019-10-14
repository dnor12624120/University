#include "Record.h"

#include <iostream>

Record::Record(const std::string& title, const std::string& location, const std::string& timeOfCreation,
			   const std::string& timeAccessed, const std::string& footagePreview):
	m_title(title),
	m_location(location),
	m_timeOfCreation(timeOfCreation),
	m_timeAccessed(timeAccessed),
	m_footagePreview(footagePreview)
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
	m_timeOfCreation;
}

void Record::setTimeAccessed(const std::string& timeAccessed)
{
	m_timeAccessed = timeAccessed;
}

void Record::setFootagePreview(const std::string& footagePreview)
{
	m_footagePreview = footagePreview;
}
