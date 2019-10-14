#include "Interface.h"
#include "Controller.h"
#include "Repository.h"
#include "CVSRepository.h"
#include "Record.h"
#include "Utility.h"
#include "HTMLUserList.h"

#include <iostream>
#include <memory>	

#define DEBUG_MODE 0

int main(int argc, char** argv)
{
	std::unique_ptr<CVSRepository<std::string, Record>> repository(new CVSRepository<std::string, Record>());
	std::unique_ptr<Controller> controller(new Controller(std::move(repository)));
	std::unique_ptr<Interface> interface(new Interface(std::move(controller)));
	interface->run();
	return 0;
}

