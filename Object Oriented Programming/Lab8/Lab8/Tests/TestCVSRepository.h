#pragma once

#include "Record.h"
#include "CVSRepository.h"
#include "Exception.h"

#include <iostream>
#include <string>
#include <cassert>

#define DEFAULT_TITLE "Title"
#define DEFAULT_LOCATION "Location"
#define DEFAULT_TIME_OF_CREATION "01-01-0001"
#define DEFAULT_TIME_ACCESSED "1"
#define DEFAULT_FOOTAGE_PREVIEW "Preview"

class TestCVSRepository
{
	public:
		static void CreateDefault_NoInput_NoException()
		{
			bool exceptionThrown = false;
			try
			{
				CVSRepository<std::string, Record> repository = CVSRepository<std::string, Record>();
			}
			catch (std::exception& exception)
			{
				exceptionThrown = true;
			}
			assert(exceptionThrown == false);
		}

		static void CreateWithFilepath_DefaultFilepath_NoException()
		{
			bool exceptionThrown = false;
			try
			{
				CVSRepository<std::string, Record> repository = CVSRepository<std::string, Record>("filepath");
			}
			catch (std::exception& exception)
			{
				exceptionThrown = true;
			}
			assert(exceptionThrown == false);
		}


		static void SetFilepath_DefaultFilepath_NoException()
		{
			CVSRepository<std::string, Record> repository = CVSRepository<std::string, Record>();
			bool exceptionThrown = false;
			try
			{
				repository.setFilepath("filepath");
			}
			catch (std::exception& exception)
			{
				exceptionThrown = true;
			}
			assert(exceptionThrown == false);
		}

		static void LoadObjects_NoFilepath_NoException()
		{
			CVSRepository<std::string, Record> repository = CVSRepository<std::string, Record>();
			bool exceptionThrown = false;
			try
			{
				repository.loadObjects();
			}
			catch (std::exception& exception)
			{
				exceptionThrown = true;
			}
			assert(exceptionThrown == false);
		}

		static void LoadObjects_EmptyFile_NoException()
		{
			CVSRepository<std::string, Record> repository = CVSRepository<std::string, Record>("filepath");
			bool exceptionThrown = false;
			try
			{
				repository.loadObjects();
			}
			catch (std::exception& exception)
			{
				exceptionThrown = true;
			}
			assert(exceptionThrown == false);
		}

		static void LoadObjects_ValidFile_NoException()
		{
			CVSRepository<std::string, Record> repository = CVSRepository<std::string, Record>("Tests\\TestRepo.cvs");
			bool exceptionThrown = false;
			try
			{
				repository.loadObjects();
			}
			catch (std::exception& exception)
			{
				exceptionThrown = true;
			}
			assert(exceptionThrown == false);
		}

		static void AddObject_EmptyFilepath_NoException()
		{
			CVSRepository<std::string, Record> repository = CVSRepository<std::string, Record>();
			std::unique_ptr<Record> recordPointer = std::unique_ptr<Record>(new Record(DEFAULT_TITLE, DEFAULT_LOCATION,
																				DEFAULT_TIME_OF_CREATION, DEFAULT_TIME_ACCESSED,
																				DEFAULT_FOOTAGE_PREVIEW));
			bool exceptionThrown = false;
			try
			{
				repository.addObject(DEFAULT_TITLE, std::move(recordPointer));
			}
			catch (std::exception& exception)
			{
				exceptionThrown = true;
			}
			assert(exceptionThrown == false);
		}

		static void AddObject_ValidFilepath_NoException()
		{
			CVSRepository<std::string, Record> repository = CVSRepository<std::string, Record>();
			repository.setFilepath("Tets\\TestRepo.cvs");
			std::unique_ptr<Record> recordPointer = std::unique_ptr<Record>(new Record(DEFAULT_TITLE, DEFAULT_LOCATION,
																					   DEFAULT_TIME_OF_CREATION, DEFAULT_TIME_ACCESSED,
																					   DEFAULT_FOOTAGE_PREVIEW));
			bool exceptionThrown = false;
			try
			{
				repository.addObject(DEFAULT_TITLE, std::move(recordPointer));
			}
			catch (std::exception& exception)
			{
				exceptionThrown = true;
			}
			assert(exceptionThrown == false);
		}

		static void RemoveObject_EmptyFilepath_NoException()
		{
			CVSRepository<std::string, Record> repository = CVSRepository<std::string, Record>();
			repository.setFilepath("Tets\\TestRepo.cvs");
			std::unique_ptr<Record> recordPointer = std::unique_ptr<Record>(new Record(DEFAULT_TITLE, DEFAULT_LOCATION,
																					   DEFAULT_TIME_OF_CREATION, DEFAULT_TIME_ACCESSED,
																					   DEFAULT_FOOTAGE_PREVIEW));
			repository.addObject(DEFAULT_TITLE, std::move(recordPointer));
			bool exceptionThrown = false;
			try
			{
				repository.removeObject(DEFAULT_TITLE);
			}
			catch (std::exception& exception)
			{
				exceptionThrown = true;
			}
			assert(exceptionThrown == false);
		}

		static void RemoveObject_ValidFilepath_NoException()
		{
			CVSRepository<std::string, Record> repository = CVSRepository<std::string, Record>();
			repository.setFilepath("Tets\\TestRepo.cvs");
			std::unique_ptr<Record> defaultRecordPointer = std::unique_ptr<Record>
				(new Record("DefaultTitle", "DefaultLocation", "10-10-2010", "1", "DefaultPreview"));
			std::unique_ptr<Record> recordPointer = std::unique_ptr<Record>(new Record(DEFAULT_TITLE, DEFAULT_LOCATION,
																					   DEFAULT_TIME_OF_CREATION, DEFAULT_TIME_ACCESSED,
																					   DEFAULT_FOOTAGE_PREVIEW));
			repository.addObject(DEFAULT_TITLE, std::move(recordPointer));
			repository.addObject("DefaultTitle", std::move(defaultRecordPointer));
			bool exceptionThrown = false;
			try
			{
				repository.removeObject(DEFAULT_TITLE);
			}
			catch (std::exception& exception)
			{
				exceptionThrown = true;
			}
			assert(exceptionThrown == false);
		}

		static void TestAll()
		{
			TestCVSRepository::CreateDefault_NoInput_NoException();
			TestCVSRepository::CreateWithFilepath_DefaultFilepath_NoException();
			TestCVSRepository::SetFilepath_DefaultFilepath_NoException();
			TestCVSRepository::LoadObjects_NoFilepath_NoException();
			TestCVSRepository::LoadObjects_EmptyFile_NoException();
			TestCVSRepository::LoadObjects_ValidFile_NoException();
			TestCVSRepository::AddObject_EmptyFilepath_NoException();
			TestCVSRepository::AddObject_ValidFilepath_NoException();
			TestCVSRepository::RemoveObject_EmptyFilepath_NoException();
			TestCVSRepository::RemoveObject_ValidFilepath_NoException();
			std::cout << "TestCVSRepository ran successfully!\n";
		}
};