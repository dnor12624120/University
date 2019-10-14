#include "Interface.h"
#include "Controller.h"
#include "Repository.h"
#include "Record.h"

#include <iostream>
#include <memory>

int main(int argc, char** argv)
{
	std::unique_ptr<Repository> r(new Repository());
	std::unique_ptr<Controller> c(new Controller(std::move(r)));
	std::unique_ptr<Interface> i(new Interface(std::move(c)));
	
	i->run();
	return 0;
}