#pragma once

#include "FilterFunctions.h"
#include "Record.h"

#include <string>
#include <cassert>
#include <iostream>

#define DEFAULT_TITLE "Title"
#define DEFAULT_LOCATION "Location"
#define DEFAULT_TIME_OF_CREATION "01-01-0001"
#define DEFAULT_TIME_ACCESSED "1"
#define DEFAULT_FOOTAGE_PREVIEW "Preview"

class TestFilterFunctions
{
	public:
		static void FilterTimesAccessed_MatchingRecord_True()
		{
			Record record(DEFAULT_TITLE, DEFAULT_LOCATION, DEFAULT_TIME_OF_CREATION,
						  DEFAULT_TIME_ACCESSED, DEFAULT_FOOTAGE_PREVIEW);
			assert(filterTimesAccessed(&record, "Location", "2") == true);
		}

		static void TestAll()
		{
			TestFilterFunctions::FilterTimesAccessed_MatchingRecord_True();
			std::cout << "TestFilterFunctions ran successfully!\n";
		}
};