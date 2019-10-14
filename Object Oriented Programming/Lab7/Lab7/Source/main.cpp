#include "Interface.h"
#include "Controller.h"
#include "Repository.h"
#include "CVSRepository.h"
#include "Record.h"

#include "TestController.h"
#include "TestCVSRepository.h"
#include "TestException.h"
#include "TestFilterFunctions.h"
#include "TestRecord.h"
#include "TestRepository.h"
#include "TestUtility.h"

#include <iostream>
#include <memory>	

#define DEBUG_MODE 1

int main(int argc, char** argv)
{
	if (DEBUG_MODE)
	{
		TestController::TestAll();
		TestCVSRepository::TestAll();
		TestException::TestAll();
		TestFilterFunctions::TestAll();
		TestRecord::TestAll();
		TestRepository::TestAll();
		TestUtility::TestAll();
	}
	else
	{
		std::unique_ptr<CVSRepository<std::string, Record>> repository(new CVSRepository<std::string, Record>());
		std::unique_ptr<Controller> controller(new Controller(std::move(repository)));
		std::unique_ptr<Interface> interface(new Interface(std::move(controller)));

		interface->run();
	}
	return 0;
}

