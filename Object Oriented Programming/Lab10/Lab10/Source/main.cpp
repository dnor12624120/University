#include "Interface.h"
#include "Repository.h"
#include "CVSRepository.h"
#include "Controller.h"
#include "Record.h"
#include <QtWidgets/QApplication>

#include <memory>
#include <string>
#include <fstream>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	std::ifstream configFile("repository.cfg");
	std::string repositoryType, repositoryFilepath;
	configFile >> repositoryType >> repositoryFilepath;
	std::unique_ptr<Repository<std::string, Record>> repository;
	if (repositoryType == "memory")
	{
		repository = std::unique_ptr<Repository<std::string, Record>>(new Repository<std::string, Record>());
	}
	else
	{
		repository = std::unique_ptr<CVSRepository<std::string, Record>>(new CVSRepository<std::string, Record>());
		dynamic_cast<CVSRepository<std::string, Record>*>(repository.get())->setFilepath(repositoryFilepath);
		dynamic_cast<CVSRepository<std::string, Record>*>(repository.get())->loadObjects();

	}
	std::unique_ptr<FunctionStack> userStack(new FunctionStack);
	std::unique_ptr<FunctionStack> adminStack(new FunctionStack);
	std::unique_ptr<Controller> controller(new Controller(std::move(repository), std::move(userStack), std::move(adminStack)));
	Interface w(std::move(controller));
	w.show();
	return a.exec();
}

