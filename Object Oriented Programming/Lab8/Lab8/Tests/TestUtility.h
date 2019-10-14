#pragma once

#include "Utility.h"

#include <iostream>
#include <cassert>
#include <string>

class TestUtility
{
	public:
		static void ConvertStringToInt_NumericString_NumericalValue()
		{
			assert(convertStringToInt("123") == 123);
		}

		static void IsStringNumeric_NumericString_True()
		{
			assert(isStringNumeric("123") == true);
		}

		static void IsStringNumeric_NonNumericString_False()
		{
			assert(isStringNumeric("abc") == false);
		}

		static void IsValidDate_ValidDate_True()
		{
			assert(isValidDate("10-10-2010") == true);
		}

		static void IsValidDate_InvalidDate_False()
		{
			assert(isValidDate("InvalidDate") == false);
		}

		static void TestAll()
		{
			TestUtility::ConvertStringToInt_NumericString_NumericalValue();
			TestUtility::IsStringNumeric_NumericString_True();
			TestUtility::IsStringNumeric_NonNumericString_False();
			TestUtility::IsValidDate_ValidDate_True();
			TestUtility::IsValidDate_InvalidDate_False();
			std::cout << "TestUtility ran successfully!\n";
		}
};