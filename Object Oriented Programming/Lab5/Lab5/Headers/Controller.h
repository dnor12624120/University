#pragma once

#include "Repository.h"

#include <memory>

class Controller
{
	public:
		Controller() = default;
		Controller(std::unique_ptr<Repository> repository);


		void addRecord(const std::string& title, const std::string& location, const std::string& timeOfCreation,
					   const std::string& timeAccessed, const std::string& footagePreview);

		void updateRecord(const std::string& title, const std::string& newLocation,
						  const std::string& newTimeOfCreation, const std::string& newTimeAccessed,
						  const std::string& newFootagePreview);

		void deleteRecord(const std::string& title);

		Record* getRecord(const std::string& title) const;

		std::map<std::string, std::unique_ptr<Record>>::iterator iterator();

		std::map<std::string, std::unique_ptr<Record>>::iterator begin();

		std::map<std::string, std::unique_ptr<Record>>::iterator end();

	private:
		std::unique_ptr<Repository> m_repository;
};