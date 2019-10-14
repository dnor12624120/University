#include "AdminInterface.h"
#include "UserInterface.h"
#include "Controller.h"
#include "Repository.h"
#include "CVSRepository.h"
#include "Record.h"
#include <QtWidgets/QApplication>

#include <string>
#include <memory>
#include <fstream>

#define ADMIN_MODE_STRING "admin"
#define USER_MODE_STRING "user"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	std::ifstream config("interface.cfg");
	std::string interfaceMode;
	std::string repositoryType;
	config >> interfaceMode >> repositoryType;
	AdminInterface adminInterface;
	std::unique_ptr<Repository<std::string, Record>> repository;
	if (repositoryType == "memory")
	{
		repository = std::unique_ptr<Repository<std::string, Record>>(new Repository<std::string, Record>());
	}
	else
	{
		std::string filepath;
		config >> filepath;
		repository = std::unique_ptr<CVSRepository<std::string, Record>>(new CVSRepository<std::string, Record>());
		dynamic_cast<CVSRepository<std::string, Record>*>(repository.get())->setFilepath(filepath);
		dynamic_cast<CVSRepository<std::string, Record>*>(repository.get())->loadObjects();
	}
	std::unique_ptr<Controller> controller(new Controller(std::move(repository)));
	if (interfaceMode == "admin")
	{	
		adminInterface.setController(std::move(controller));
		adminInterface.loadList();
		adminInterface.show();
	}
	return a.exec();
}
