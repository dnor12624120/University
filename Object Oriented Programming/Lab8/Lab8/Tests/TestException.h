#pragma once

#include "Exception.h"

#include <string>
#include <cassert>
#include <iostream>

class TestException
{
	public:
		static void CreateInputException_NoInput_NoException()
		{
			try
			{
				throw InputException("Test");
			}
			catch (InputException& exception)
			{
				exception.what();
				assert(true);
			}
		}

		static void CreateRepositoryException_NoInput_NoException()
		{
			try
			{
				throw RepositoryException("Test");
			}
			catch (RepositoryException& exception)
			{
				exception.what();
				assert(true);
			}
		}

		static void TestAll()
		{
			TestException::CreateInputException_NoInput_NoException();
			TestException::CreateRepositoryException_NoInput_NoException();
			std::cout << "TestException ran successfully!\n";
		}
};