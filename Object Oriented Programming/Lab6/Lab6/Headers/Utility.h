#pragma once

#include <string>

/*
	Utility function that converts a numerical string into an integer.
*/
static const int convertStringToInt(const std::string& stringToConvert)
{
	int convertedNumber = 0;
	for (int i = 0; i < stringToConvert.length(); i++)
	{
		convertedNumber = convertedNumber * 10 + (stringToConvert[i] - '0');
	}
	return convertedNumber;
}

/*
	Utility function that checks if a given string only contains digit characters (0-9).
*/
static const bool isStringNumeric(const std::string& stringToCheck)
{
	for (int i = 0; i < stringToCheck.length(); i++)
	{
		if (isdigit(stringToCheck[i]))
		{
			return false;
		}
	}
	return true;
}

/*
	Utility function that checks if a string is in a valid DD-MM-YYYY format.
*/
static const bool isValidDate(const std::string& date)
{
	return
		isStringNumeric(date.substr(0, 2)) && isStringNumeric(date.substr(3, 2)) && isStringNumeric(date.substr(6, 4));
}