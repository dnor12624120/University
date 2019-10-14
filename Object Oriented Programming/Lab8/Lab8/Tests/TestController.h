#pragma once

#include "Controller.h"
#include "Record.h"
#include "Repository.h"
#include "CVSRepository.h"
#include "Exception.h"
#include "Interface.h"
#include "FakeRepository.h"

#include <iostream>
#include <string>
#include <memory>
#include <cassert>

#define DEFAULT_TITLE "Title"
#define DEFAULT_LOCATION "Location"
#define DEFAULT_TIME_OF_CREATION "01-01-0001"
#define DEFAULT_TIME_ACCESSED "1"
#define DEFAULT_FOOTAGE_PREVIEW "Preview"

class TestController
{
	public:
		static void AddRecord_ValidFields_NoException()
		{
			std::unique_ptr<Repository<std::string, Record>> repository(new FakeRepository<std::string, Record>());
			Controller controller(std::move(repository));
			bool exceptionThrown = false;
			try
			{
				controller.addRecord(DEFAULT_TITLE, DEFAULT_LOCATION, DEFAULT_TIME_OF_CREATION,
									 DEFAULT_TIME_ACCESSED, DEFAULT_FOOTAGE_PREVIEW);
			}
			catch (std::exception& exception)
			{
				exceptionThrown = true;
			}
			assert(exceptionThrown == false);
		}

		static void AddRecord_DuplicateKey_RepositoryException()
		{
			std::unique_ptr<Repository<std::string, Record>> repository(new FakeRepository<std::string, Record>());
			Controller controller(std::move(repository));
			bool exceptionThrown = false;
			controller.addRecord(DEFAULT_TITLE, DEFAULT_LOCATION, DEFAULT_TIME_OF_CREATION,
								 DEFAULT_TIME_ACCESSED, DEFAULT_FOOTAGE_PREVIEW);
			try
			{
				controller.addRecord(DEFAULT_TITLE, DEFAULT_LOCATION, DEFAULT_TIME_OF_CREATION,
									 DEFAULT_TIME_ACCESSED, DEFAULT_FOOTAGE_PREVIEW);
			}
			catch (std::exception& exception)
			{
				exceptionThrown = true;
			}
			assert(exceptionThrown == true);
		}

		static void UpdateRecord_ValidFields_NoException()
		{
			std::unique_ptr<Repository<std::string, Record>> repository(new FakeRepository<std::string, Record>());
			Controller controller(std::move(repository));
			bool exceptionThrown = false;
			controller.addRecord(DEFAULT_TITLE, DEFAULT_LOCATION, DEFAULT_TIME_OF_CREATION,
								 DEFAULT_TIME_ACCESSED, DEFAULT_FOOTAGE_PREVIEW);
			try
			{
				controller.updateRecord(DEFAULT_TITLE, "NewLocation", "02-02-0002", "2", "NewPreview");
			}
			catch (std::exception& exception)
			{
				exceptionThrown = true;
			}
			assert(exceptionThrown == false);
		}

		static void UpdateRecord_InexistentKey_RepositoryException()
		{
			std::unique_ptr<Repository<std::string, Record>> repository(new FakeRepository<std::string, Record>());
			Controller controller(std::move(repository));
			bool exceptionThrown = false;
			controller.addRecord(DEFAULT_TITLE, DEFAULT_LOCATION, DEFAULT_TIME_OF_CREATION,
								 DEFAULT_TIME_ACCESSED, DEFAULT_FOOTAGE_PREVIEW);
			try
			{
				controller.updateRecord("NewTitle", "NewLocation", "02-02-0002", "2", "NewPreview");
			}
			catch (std::exception& exception)
			{
				exceptionThrown = true;
			}
			assert(exceptionThrown == true);
		}

		static void DeleteRecord_ValidKey_NoException()
		{
			std::unique_ptr<Repository<std::string, Record>> repository(new FakeRepository<std::string, Record>());
			Controller controller(std::move(repository));
			bool exceptionThrown = false;
			controller.addRecord(DEFAULT_TITLE, DEFAULT_LOCATION, DEFAULT_TIME_OF_CREATION,
								 DEFAULT_TIME_ACCESSED, DEFAULT_FOOTAGE_PREVIEW);
			try
			{
				controller.deleteRecord(DEFAULT_TITLE);
			}
			catch (std::exception& exception)
			{
				exceptionThrown = true;
			}
			assert(exceptionThrown == false);
		}

		static void DeleteRecord_InexistentKey_RepositoryException()
		{
			std::unique_ptr<Repository<std::string, Record>> repository(new FakeRepository<std::string, Record>());
			Controller controller(std::move(repository));
			bool exceptionThrown = false;
			try
			{
				controller.deleteRecord(DEFAULT_TITLE);
			}
			catch (std::exception& exception)
			{
				exceptionThrown = true;
			}
			assert(exceptionThrown == true);
		}

		static void GetObject_ValidKey_NoException()
		{
			std::unique_ptr<Repository<std::string, Record>> repository(new FakeRepository<std::string, Record>());
			Controller controller(std::move(repository));
			bool exceptionThrown = false;
			controller.addRecord(DEFAULT_TITLE, DEFAULT_LOCATION, DEFAULT_TIME_OF_CREATION,
								 DEFAULT_TIME_ACCESSED, DEFAULT_FOOTAGE_PREVIEW);
			try
			{
				controller.getRecord(DEFAULT_TITLE);
			}
			catch (std::exception& exception)
			{
				exceptionThrown = true;
			}
			assert(exceptionThrown == false);
		}

		static void CreateIterator_NoInput_NoException()
		{
			std::unique_ptr<Repository<std::string, Record>> repository(new FakeRepository<std::string, Record>());
			Controller controller(std::move(repository));
			bool exceptionThrown = false;
			try
			{
				controller.iterator();
			}
			catch (std::exception& exception)
			{
				exceptionThrown = true;
			}
			assert(exceptionThrown == false);
		}

		static void IteratorBegin_NoInput_NoException()
		{
			std::unique_ptr<Repository<std::string, Record>> repository(new FakeRepository<std::string, Record>());
			Controller controller(std::move(repository));
			bool exceptionThrown = false;
			try
			{
				controller.begin();
			}
			catch (std::exception& exception)
			{
				exceptionThrown = true;
			}
			assert(exceptionThrown == false);
		}

		static void IteratorEnd_NoInput_NoException()
		{
			std::unique_ptr<Repository<std::string, Record>> repository(new FakeRepository<std::string, Record>());
			Controller controller(std::move(repository));
			bool exceptionThrown = false;
			try
			{
				controller.end();
			}
			catch (std::exception& exception)
			{
				exceptionThrown = true;
			}
			assert(exceptionThrown == false);
		}

		static void TestAll()
		{
			TestController::AddRecord_ValidFields_NoException();
			TestController::UpdateRecord_ValidFields_NoException();
			TestController::DeleteRecord_ValidKey_NoException();
			TestController::GetObject_ValidKey_NoException();
			TestController::CreateIterator_NoInput_NoException();
			TestController::IteratorBegin_NoInput_NoException();
			TestController::IteratorEnd_NoInput_NoException();
			std::cout << "TestController ran successfully!\n";
		}
};