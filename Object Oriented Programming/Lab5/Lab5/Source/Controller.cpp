#include "Controller.h"
#include "Record.h"

Controller::Controller(std::unique_ptr<Repository> repository):
	m_repository(std::move(repository))
{

}

void Controller::addRecord(const std::string& title, const std::string& location, const std::string& timeOfCreation,
						   const std::string& timeAccessed, const std::string& footagePreview)
{
	try
	{
		std::unique_ptr<Record> record = std::unique_ptr<Record>(new Record(title, location, timeOfCreation, timeAccessed, footagePreview));
		m_repository->addElement(title, std::move(record));
	}
	catch (std::exception& e)
	{

	}
}

void Controller::updateRecord(const std::string& title, const std::string& newLocation,
							  const std::string& newTimeOfCreation, const std::string& newTimeAccessed,
							  const std::string& newFootagePreview)
{
	try
	{
		m_repository->removeElement(title);
		std::unique_ptr<Record> newRecord = std::unique_ptr<Record>(new Record(title, newLocation,
																				newTimeOfCreation, newTimeAccessed, newFootagePreview));
		m_repository->addElement(title, std::move(newRecord));
	}
	catch (std::exception& e)
	{

	}
}

void Controller::deleteRecord(const std::string& title)
{
	try
	{
		m_repository->removeElement(title);
	}
	catch (std::exception& e)
	{

	}
}

Record* Controller::getRecord(const std::string& title) const
{
	try
	{
		Record* record = m_repository->getRecord(title);
		return record;
	}
	catch (std::exception& e)
	{

	}
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