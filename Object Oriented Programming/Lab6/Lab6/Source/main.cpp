#include "Interface.h"
#include "Controller.h"
#include "Repository.h"
#include "Record.h"

#include <iostream>
#include <memory>

int main(int argc, char** argv)
{
	std::unique_ptr<Repository> repository(new Repository());
	std::unique_ptr<Controller> controller(new Controller(std::move(repository)));
	std::unique_ptr<Interface> interface(new Interface(std::move(controller)));

	interface->run();
	return 0;
}