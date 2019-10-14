#pragma once

#include "Record.h"
#include "Repository.h"
#include "Exception.h"
#include <memory>
#include <string>
#include <cassert>
#include <iostream>

#define DEFAULT_TITLE "Title"
#define DEFAULT_LOCATION "Location"
#define DEFAULT_TIME_OF_CREATION "01-01-0001"
#define DEFAULT_TIME_ACCESSED "1"
#define DEFAULT_FOOTAGE_PREVIEW "Preview"

class TestRepository
{
	public:
		static void AddObject_DefaultObject_NoException()
		{
			Repository<std::string, Record> repository;
			std::unique_ptr<Record> record = std::unique_ptr<Record>(new Record(DEFAULT_TITLE, DEFAULT_LOCATION,
													  DEFAULT_TIME_OF_CREATION, DEFAULT_TIME_ACCESSED,
													  DEFAULT_FOOTAGE_PREVIEW));
			repository.addObject(DEFAULT_TITLE, std::move(record));
			Record returnedRecord = repository.getObject(DEFAULT_TITLE);
			assert(returnedRecord.getTitle() == DEFAULT_TITLE);
			assert(returnedRecord.getLocation() == DEFAULT_LOCATION);
			assert(returnedRecord.getTimeOfCreation() == DEFAULT_TIME_OF_CREATION);
			assert(returnedRecord.getTimeAccessed() == DEFAULT_TIME_ACCESSED);
			assert(returnedRecord.getFootagePreview() == DEFAULT_FOOTAGE_PREVIEW);
		}

		static void AddObject_DuplicateObject_RepositoryException()
		{
			Repository<std::string, Record> repository;
			bool exceptionThrown = false;
			std::unique_ptr<Record> record = std::unique_ptr<Record>(new Record(DEFAULT_TITLE, DEFAULT_LOCATION,
																				DEFAULT_TIME_OF_CREATION, DEFAULT_TIME_ACCESSED,
																				DEFAULT_FOOTAGE_PREVIEW));
			std::unique_ptr<Record> duplicateRecord = std::unique_ptr<Record>(new Record(DEFAULT_TITLE, DEFAULT_LOCATION,
																				DEFAULT_TIME_OF_CREATION, DEFAULT_TIME_ACCESSED,
																				DEFAULT_FOOTAGE_PREVIEW));
			repository.addObject(DEFAULT_TITLE, std::move(record));
			try
			{
				repository.addObject(DEFAULT_TITLE, std::move(duplicateRecord));
			}
			catch (RepositoryException& exception)
			{ 
				exceptionThrown = true;
			}
			assert(exceptionThrown == true);
		}

		static void RemoveObject_ExistingObject_NoException()
		{
			Repository<std::string, Record> repository;
			bool exceptionThrown = false;
			std::unique_ptr<Record> record = std::unique_ptr<Record>(new Record(DEFAULT_TITLE, DEFAULT_LOCATION,
																				DEFAULT_TIME_OF_CREATION, DEFAULT_TIME_ACCESSED,
																				DEFAULT_FOOTAGE_PREVIEW));
			repository.addObject(DEFAULT_TITLE, std::move(record));
			try
			{
				repository.removeObject(DEFAULT_TITLE);
			}
			catch (RepositoryException& exception)
			{
				exceptionThrown = true;
			}
			assert(exceptionThrown == false);
		}

		static void RemoveObject_NonexistentObject_RepositoryException()
		{
			Repository<std::string, Record> repository;
			bool exceptionThrown = false;
			try
			{
				repository.removeObject(DEFAULT_TITLE);
			}
			catch (RepositoryException& exception)
			{
				exceptionThrown = true;
			}
			assert(exceptionThrown == true);
		}

		static void GetObject_ExistingObject_NoException()
		{
			Repository<std::string, Record> repository;
			bool exceptionThrown = false;
			std::unique_ptr<Record> record = std::unique_ptr<Record>(new Record(DEFAULT_TITLE, DEFAULT_LOCATION,
																				DEFAULT_TIME_OF_CREATION, DEFAULT_TIME_ACCESSED,
																				DEFAULT_FOOTAGE_PREVIEW));
			repository.addObject(DEFAULT_TITLE, std::move(record));
			Record returnedRecord;
			try
			{
				returnedRecord = repository.getObject(DEFAULT_TITLE);
			}
			catch (RepositoryException& exception)
			{
				exceptionThrown = true;
			}
			assert(exceptionThrown == false);
			assert(returnedRecord.getTitle() == DEFAULT_TITLE);
			assert(returnedRecord.getLocation() == DEFAULT_LOCATION);
			assert(returnedRecord.getTimeOfCreation() == DEFAULT_TIME_OF_CREATION);
			assert(returnedRecord.getTimeAccessed() == DEFAULT_TIME_ACCESSED);
			assert(returnedRecord.getFootagePreview() == DEFAULT_FOOTAGE_PREVIEW);
		}

		static void GetObject_InexistentObject_RepositoryException()
		{
			Repository<std::string, Record> repository;
			bool exceptionThrown = false;
			Record returnedRecord;
			try
			{
				returnedRecord = repository.getObject(DEFAULT_TITLE);
			}
			catch (RepositoryException& exception)
			{
				exceptionThrown = true;
			}
			assert(exceptionThrown == true);
		}

		static void CreateIterator_NoInput_NoException()
		{
			Repository<std::string, Record> repository;
			bool exceptionThrown = false;
			try
			{
				auto iterator = repository.iterator();
			}
			catch (std::exception& exception)
			{
				exceptionThrown = true;
			}
			assert(exceptionThrown == false);
		}

		static void IteratorBegin_NoInput_NoException()
		{
			Repository<std::string, Record> repository;
			std::unique_ptr<Record> record = std::unique_ptr<Record>(new Record(DEFAULT_TITLE, DEFAULT_LOCATION,
																				DEFAULT_TIME_OF_CREATION, DEFAULT_TIME_ACCESSED,
																				DEFAULT_FOOTAGE_PREVIEW));
			repository.addObject(DEFAULT_TITLE, std::move(record));
			auto iterator = repository.begin();
			assert(iterator->first == DEFAULT_TITLE);
		}

		static void IteratorEnd_NoInput_NoException()
		{
			Repository<std::string, Record> repository;
			bool exceptionThrown = false;
			try
			{
				auto iterator = repository.end();
			}
			catch (std::exception& exception)
			{
				exceptionThrown = true;
			}
			assert(exceptionThrown == false);
		}

		static void FilterObjects_NoMatch_EmptyVector()
		{
			Repository<std::string, Record> repository;
			std::unique_ptr<Record> record1 = std::unique_ptr<Record>(new Record("Title1", "Location1",
																				"01-01-0001", "1", "Preview1"));
			std::unique_ptr<Record> record2 = std::unique_ptr<Record>(new Record("Title2", "Location2",
																				"02-02-0002", "2", "Preview2"));
			std::unique_ptr<Record> record3 = std::unique_ptr<Record>(new Record("Title3", "Location3",
																				"03-03-0003", "3", "Preview3"));
			repository.addObject("Title1", std::move(record1));
			repository.addObject("Title2", std::move(record2));
			repository.addObject("Title3", std::move(record3));
			auto filteredRecords = repository.filter([](const auto& record){ return record->getTitle() == "Title";  });
			assert(filteredRecords.size() == 0);
		}

		static void FilterObjects_AllMatch_FullVector()
		{
			Repository<std::string, Record> repository;
			std::unique_ptr<Record> record1 = std::unique_ptr<Record>(new Record("Title1", "Location",
																				 "01-01-0001", "1", "Preview1"));
			std::unique_ptr<Record> record2 = std::unique_ptr<Record>(new Record("Title2", "Location",
																				 "02-02-0002", "2", "Preview2"));
			std::unique_ptr<Record> record3 = std::unique_ptr<Record>(new Record("Title3", "Location",
																				 "03-03-0003", "3", "Preview3"));
			repository.addObject("Title1", std::move(record1));
			repository.addObject("Title2", std::move(record2));
			repository.addObject("Title3", std::move(record3));
			auto filteredRecords = repository.filter([](const auto& record){ return record->getLocation() == "Location";  });
			assert(filteredRecords.size() == 3);
		}

		static void GetSize_OneObject_1()
		{
			Repository<std::string, Record> repository;
			std::unique_ptr<Record> record = std::unique_ptr<Record>(new Record(DEFAULT_TITLE, DEFAULT_LOCATION,
																				DEFAULT_TIME_OF_CREATION, DEFAULT_TIME_ACCESSED,
																				DEFAULT_FOOTAGE_PREVIEW));
			repository.addObject(DEFAULT_TITLE, std::move(record));
			assert(repository.size() == 1);
		}

		static void Clear_NoInput_NoException()
		{
			Repository<std::string, Record> repository;
			bool exceptionThrown = false;
			std::unique_ptr<Record> record = std::unique_ptr<Record>(new Record(DEFAULT_TITLE, DEFAULT_LOCATION,
																				DEFAULT_TIME_OF_CREATION, DEFAULT_TIME_ACCESSED,
																				DEFAULT_FOOTAGE_PREVIEW));
			repository.addObject(DEFAULT_TITLE, std::move(record));
			try
			{
				repository.clear();
			}
			catch (std::exception& exception)
			{
				exceptionThrown = true;
			}
			assert(exceptionThrown == false);
		}

		static void TestAll()
		{
			TestRepository::AddObject_DefaultObject_NoException();
			TestRepository::AddObject_DuplicateObject_RepositoryException();
			TestRepository::RemoveObject_ExistingObject_NoException();
			TestRepository::RemoveObject_NonexistentObject_RepositoryException();
			TestRepository::GetObject_ExistingObject_NoException();
			TestRepository::GetObject_InexistentObject_RepositoryException();
			TestRepository::CreateIterator_NoInput_NoException();
			TestRepository::IteratorBegin_NoInput_NoException();
			TestRepository::IteratorEnd_NoInput_NoException();
			TestRepository::FilterObjects_NoMatch_EmptyVector();
			TestRepository::FilterObjects_AllMatch_FullVector();
			TestRepository::GetSize_OneObject_1();
			TestRepository::Clear_NoInput_NoException();
			std::cout << "TestRepository ran successfully!\n";
		}
};