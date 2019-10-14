#pragma once

#include <cassert>
#include <string>
#include <sstream>
#include <iostream>
#include "Record.h"

#define DEFAULT_TITLE "Title"
#define DEFAULT_LOCATION "Location"
#define DEFAULT_TIME_OF_CREATION "01-01-0001"
#define DEFAULT_TIME_ACCESSED "1"
#define DEFAULT_FOOTAGE_PREVIEW "Preview"

class TestRecord
{
	public:
		static void CreateByValue_ValidInput_NoException()
		{
			bool exceptionThrown = false;
			try
			{
				Record record(DEFAULT_TITLE, DEFAULT_LOCATION, DEFAULT_TIME_OF_CREATION, DEFAULT_TIME_ACCESSED, DEFAULT_FOOTAGE_PREVIEW);
			}
			catch (std::exception& exception)
			{
				exceptionThrown = true;
			}
			assert(exceptionThrown == false);
		}

		static void CreateByPointer_ValidInput_NoException()
		{
			bool exceptionThrown = false;
			Record record(DEFAULT_TITLE, DEFAULT_LOCATION, DEFAULT_TIME_OF_CREATION, DEFAULT_TIME_ACCESSED, DEFAULT_FOOTAGE_PREVIEW);
			try
			{
				Record pointerRecord(&record);
			}
			catch (std::exception& exception)
			{
				exceptionThrown = true;
			}
			assert(exceptionThrown == false);
		}

		static void SetTitle_ValidInput_NoException()
		{
			Record record;
			record.setTitle(DEFAULT_TITLE);
			assert(record.getTitle() == DEFAULT_TITLE);
		}

		static void SetLocation_ValidInput_NoException()
		{
			Record record;
			record.setLocation(DEFAULT_LOCATION);
			assert(record.getLocation() == DEFAULT_LOCATION);
		}

		static void SetTimeOfCreation_ValidInput_NoException()
		{
			Record record;
			record.setTimeOfCreation(DEFAULT_TIME_OF_CREATION);
			assert(record.getTimeOfCreation() == DEFAULT_TIME_OF_CREATION);
		}

		static void SetTimeAccessed_ValidInput_NoException()
		{
			Record record;
			record.setTimeAccessed(DEFAULT_TIME_ACCESSED);
			assert(record.getTimeAccessed() == DEFAULT_TIME_ACCESSED);
		}

		static void SetFootagePreview_ValidInput_NoException()
		{
			Record record;
			record.setFootagePreview(DEFAULT_FOOTAGE_PREVIEW);
			assert(record.getFootagePreview() == DEFAULT_FOOTAGE_PREVIEW);
		}

		static void GetTitle_ValidTitle_NoException()
		{
			Record record(DEFAULT_TITLE, DEFAULT_LOCATION, DEFAULT_TIME_OF_CREATION, DEFAULT_TIME_ACCESSED, DEFAULT_FOOTAGE_PREVIEW);
			assert(record.getTitle() == DEFAULT_TITLE);
		}

		static void GetLocation_ValidLocation_NoException()
		{
			Record record(DEFAULT_TITLE, DEFAULT_LOCATION, DEFAULT_TIME_OF_CREATION, DEFAULT_TIME_ACCESSED, DEFAULT_FOOTAGE_PREVIEW);
			assert(record.getLocation() == DEFAULT_LOCATION);
		}

		static void GetTimeOfCreation_ValidTimeOfCreation_NoException()
		{
			Record record(DEFAULT_TITLE, DEFAULT_LOCATION, DEFAULT_TIME_OF_CREATION, DEFAULT_TIME_ACCESSED, DEFAULT_FOOTAGE_PREVIEW);
			assert(record.getTimeOfCreation() == DEFAULT_TIME_OF_CREATION);
		}

		static void GetTimeAccessed_ValidTimeAccessed_NoException()
		{
			Record record(DEFAULT_TITLE, DEFAULT_LOCATION, DEFAULT_TIME_OF_CREATION, DEFAULT_TIME_ACCESSED, DEFAULT_FOOTAGE_PREVIEW);
			assert(record.getTimeAccessed() == DEFAULT_TIME_ACCESSED);
		}

		static void GetFootagePreview_ValidFootagePreview_NoException()
		{
			Record record(DEFAULT_TITLE, DEFAULT_LOCATION, DEFAULT_TIME_OF_CREATION, DEFAULT_TIME_ACCESSED, DEFAULT_FOOTAGE_PREVIEW);
			assert(record.getFootagePreview() == DEFAULT_FOOTAGE_PREVIEW);
		}

		static void ReadRecord_ValidInput_NoException()
		{
			std::string data = "Title,Location,01-01-0001,1,Preview";
			std::stringstream stringstream(data);
			Record record;
			stringstream >> record;
			assert(record.getTitle() == DEFAULT_TITLE);
			assert(record.getLocation() == DEFAULT_LOCATION);
			assert(record.getTimeOfCreation() == DEFAULT_TIME_OF_CREATION);
			assert(record.getTimeAccessed() == DEFAULT_TIME_ACCESSED);
			assert(record.getFootagePreview() == DEFAULT_FOOTAGE_PREVIEW);
		}

		static void ReadRecord_InvalidInput_StandardException()
		{
			std::stringstream stringstream;
			Record record;
			bool exceptionThrown = false;
			try
			{
				stringstream >> record;
			}
			catch (std::exception& exception)
			{
				exceptionThrown = true;
			}
			assert(exceptionThrown == true);
		}

		static void PrintRecord_ValidRecord_NoException()
		{
			Record record(DEFAULT_TITLE, "Location", "01-01-0001", "1", "Preview");
			std::string data = "Title,Location,01-01-0001,1,Preview";
			std::stringstream stringstream;
			stringstream << record;
			assert(stringstream.str() == data);
		}

		static void TestAll()
		{
			TestRecord::CreateByValue_ValidInput_NoException();
			TestRecord::CreateByPointer_ValidInput_NoException();
			TestRecord::SetTitle_ValidInput_NoException();
			TestRecord::SetLocation_ValidInput_NoException();
			TestRecord::SetTimeOfCreation_ValidInput_NoException();
			TestRecord::SetTimeAccessed_ValidInput_NoException();
			TestRecord::SetFootagePreview_ValidInput_NoException();
			TestRecord::GetTitle_ValidTitle_NoException();
			TestRecord::GetLocation_ValidLocation_NoException();
			TestRecord::GetTimeOfCreation_ValidTimeOfCreation_NoException();
			TestRecord::GetTimeAccessed_ValidTimeAccessed_NoException();
			TestRecord::GetFootagePreview_ValidFootagePreview_NoException();
			TestRecord::ReadRecord_ValidInput_NoException();
			TestRecord::ReadRecord_InvalidInput_StandardException();
			TestRecord::PrintRecord_ValidRecord_NoException();
			std::cout << "TestRecord ran successfully!\n";
		}
};