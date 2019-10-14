#pragma once

#include "Record.h"
#include "Utility.h"

#include <string>
#include <iostream>

/*
	Filter function that checks whether a record's location is equal to location and its timesAccessed is
	less than timesAccessed.
*/
static bool filterTimesAccessed(Record const* record, const std::string& location, const std::string& timesAccessed)
{
	return record->getLocation() == location && convertStringToInt(record->getTimeAccessed()) < convertStringToInt(timesAccessed);
}