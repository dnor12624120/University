#include "Interface.h"
#include "Utility.h"
#include "FilterFunctions.h"
#include "InputValidator.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>

#define NUM_OF_FUNCTIONS 11

#define EXIT_INDEX 0
#define MODE_INDEX 1
#define ADD_INDEX 2
#define UPDATE_INDEX 3
#define DELETE_INDEX 4
#define LIST_ALL_INDEX 5
#define NEXT_INDEX 6
#define SAVE_INDEX 7
#define USER_LIST_INDEX 8
#define LIST_TIMES_ACCESSED_INDEX 9
#define SET_FILEPATH_INDEX 10

#define EXIT_ARGUMENT_COUNT 0
#define MODE_ARGUMENT_COUNT 1
#define ADD_ARGUMENT_COUNT 5
#define UPDATE_ARGUMENT_COUNT 5
#define DELETE_ARGUMENT_COUNT 1
#define LIST_ALL_ARGUMENT_COUNT 0
#define NEXT_ARGUMENT_COUNT 0
#define SAVE_ARGUMENT_COUNT 1
#define USER_LIST_ARGUMENT_COUNT 0
#define LIST_TIMES_ACCESSED_ARGUMENT_COUNT 2
#define SET_FILEPATH_ARGUMENT_COUNT 1

#define ADMINISTRATOR_ACCESS "A"
#define USER_ACCESS "U"

#define ACCESS_MODE_INDEX 1
#define ADD_TITLE_INDEX 1
#define ADD_LOCATION_INDEX 2
#define ADD_CREATION_TIME_INDEX 3
#define ADD_ACCESSS_TIME_INDEX 4
#define ADD_FOOTAGE_INDEX 5
#define UPDATE_TITLE_INDEX 1
#define UPDATE_NEW_LOCATION_INDEX 2
#define UPDATE_NEW_CREATION_TIME_INDEX 3
#define UPDATE_NEW_ACCESS_TIME_INDEX 4
#define UPDATE_NEW_FOOTAGE_INDEX 5
#define REMOVE_TITLE_INDEX 1
#define SAVE_TITLE_INDEX 1
#define LIST_TIMES_ACCESSED_LOCATION_INDEX 1
#define LIST_TIMES_ACCESSED_TIMES_ACCESSED_INDEX 2
#define SET_FILEPATH_FILEPATH_INDEX 1

Interface::Interface(std::unique_ptr<Controller> controller):
	m_controller(std::move(controller)),
	m_running(true),
	m_currentAccess(InterfaceAccess::USER),
	m_inputValidator(std::unique_ptr<InputValidator>(new InputValidator(*this)))
{
	// initialize command vector
	m_commands.insert(std::make_pair<std::string, Command>("exit", Command("exit", EXIT_ARGUMENT_COUNT, EXIT_INDEX)));
	m_commands.insert(std::make_pair<std::string, Command>("mode", Command("mode", MODE_ARGUMENT_COUNT, MODE_INDEX)));
	m_commands.insert(std::make_pair<std::string, Command>("add", Command("add", ADD_ARGUMENT_COUNT, ADD_INDEX)));
	m_commands.insert(std::make_pair<std::string, Command>("update", Command("update", UPDATE_ARGUMENT_COUNT, UPDATE_INDEX)));
	m_commands.insert(std::make_pair<std::string, Command>("delete", Command("delete", DELETE_ARGUMENT_COUNT, DELETE_INDEX)));
	m_commands.insert(std::make_pair<std::string, Command>("list"	, Command("list", LIST_ALL_ARGUMENT_COUNT, LIST_ALL_INDEX)));
	m_commands.insert(std::make_pair<std::string, Command>("next", Command("next", NEXT_ARGUMENT_COUNT, NEXT_INDEX)));
	m_commands.insert(std::make_pair<std::string, Command>("save", Command("save", SAVE_ARGUMENT_COUNT, SAVE_INDEX)));
	m_commands.insert(std::make_pair<std::string, Command>("mylist", Command("mylist", USER_LIST_ARGUMENT_COUNT, USER_LIST_INDEX)));
	m_commands.insert(std::make_pair<std::string, Command>("list", Command("list", LIST_TIMES_ACCESSED_ARGUMENT_COUNT, LIST_TIMES_ACCESSED_INDEX)));
	m_commands.insert(std::make_pair<std::string, Command>("fileLocation", Command("fileLocation", SET_FILEPATH_ARGUMENT_COUNT, SET_FILEPATH_INDEX)));
	// initialize function pointer vector
	m_functions.resize(NUM_OF_FUNCTIONS);
	m_functions[EXIT_INDEX] = std::bind(&Interface::exit, this, std::placeholders::_1);
	m_functions[MODE_INDEX] = std::bind(&Interface::changeAccess, this, std::placeholders::_1);
	m_functions[ADD_INDEX] = std::bind(&Interface::addRecord, this, std::placeholders::_1);
	m_functions[UPDATE_INDEX] = std::bind(&Interface::updateRecord, this, std::placeholders::_1);
	m_functions[DELETE_INDEX] = std::bind(&Interface::removeRecord, this, std::placeholders::_1);
	m_functions[LIST_ALL_INDEX] = std::bind(&Interface::listAll, this, std::placeholders::_1);
	m_functions[NEXT_INDEX] = std::bind(&Interface::next, this, std::placeholders::_1);
	m_functions[SAVE_INDEX] = std::bind(&Interface::save, this, std::placeholders::_1);
	m_functions[USER_LIST_INDEX] = std::bind(&Interface::userList, this, std::placeholders::_1);
	m_functions[LIST_TIMES_ACCESSED_INDEX] = std::bind(&Interface::listTimesAccessed, this, std::placeholders::_1);
	m_functions[SET_FILEPATH_INDEX] = std::bind(&Interface::setFilepath, this, std::placeholders::_1);
}

void Interface::run()
{
	std::string input;
	while (m_running)
	{
		try
		{
			getInput(input);
			std::vector<std::string> arguments = parseInput(input);
			m_inputValidator->validateInput(arguments[0], arguments.size() - 1);
			int index = getCommandIndex(arguments[0], arguments.size() - 1);
			m_functions[index](arguments);
		}
		catch (std::exception& exception)
		{
			std::cout << exception.what() << '\n';
		}
	}
}

void Interface::getInput(std::string& input)
{
	std::cout << ">";
	std::getline(std::cin, input);
}

std::vector<std::string> Interface::parseInput(const std::string& input)
{
	std::vector<std::string> arguments;
	std::string argument;
	std::stringstream stringstreamInput(input);

	std::getline(stringstreamInput, argument, ' ');
	arguments.emplace_back(argument);

	while (std::getline(stringstreamInput, argument, ','))
	{
		arguments.emplace_back(argument);
	}

	for (std::string i : arguments)
	{
		if (i[0] == ' ')
		{
			i.erase(0, 1);
		}
	}

	return arguments;
}

int Interface::getCommandIndex(const std::string& command, int argumentCount)
{
	for (auto iterator = m_commands.begin(); iterator != m_commands.end(); iterator++)
	{
		std::string iteratorKey = iterator->first;
		Command iteratorCommand = iterator->second;
		if (iteratorKey == command && iteratorCommand.argumentCount == argumentCount)
		{
			return iteratorCommand.index;
		}
	}
}

void Interface::exit(const std::vector<std::string>& arguments)
{
	m_running = false;
}

void Interface::changeAccess(const std::vector<std::string>& arguments)
{
	if (arguments[ACCESS_MODE_INDEX] == "A")
	{
		m_currentAccess = InterfaceAccess::ADMIN;
	}
	else if (arguments[ACCESS_MODE_INDEX] == "B")
	{
		m_currentAccess = InterfaceAccess::USER;
	}
	else
	{
		throw std::exception("Invalid access mode!");
	}
	m_controller->setUser(m_currentAccess);
}

void Interface::addRecord(const std::vector<std::string>& arguments)
{
	if (m_currentAccess != InterfaceAccess::ADMIN)
	{
		throw std::exception("Must have admin privileges to add a record!");
	}
	if (!isValidDate(arguments[ADD_CREATION_TIME_INDEX]))
	{
		throw std::exception("Invalid date!");
	}
	if (!isStringNumeric(arguments[ADD_ACCESSS_TIME_INDEX]))
	{
		throw std::exception("Invalid access time!");
	}
	try
	{
		m_controller->addRecord(arguments[ADD_TITLE_INDEX],
								arguments[ADD_LOCATION_INDEX],
								arguments[ADD_CREATION_TIME_INDEX],
								arguments[ADD_ACCESSS_TIME_INDEX],
								arguments[ADD_FOOTAGE_INDEX]);
	}
	catch (std::exception& exception)
	{
		std::cout << exception.what() << '\n';
	}
}

void Interface::removeRecord(const std::vector<std::string>& arguments)
{
	if (m_currentAccess != InterfaceAccess::ADMIN)
	{
		throw std::exception("Must have admin privileges to remove a record!");
	}
	try
	{
		m_controller->deleteRecord(arguments[REMOVE_TITLE_INDEX]);
	}
	catch (std::exception& exception)
	{
		std::cout << exception.what() << '\n';
	}
}

void Interface::updateRecord(const std::vector<std::string>& arguments)
{
	if (m_currentAccess != InterfaceAccess::ADMIN)
	{
		throw std::exception("Must have admin privileges to update a record!");
	}
	if (!isValidDate(arguments[UPDATE_NEW_CREATION_TIME_INDEX]))
	{
		throw std::exception("Invalid date!");
	}
	if (!isStringNumeric(arguments[UPDATE_NEW_ACCESS_TIME_INDEX]))
	{
		throw std::exception("Invalid access time!");
	}
	try
	{
		m_controller->updateRecord(arguments[UPDATE_TITLE_INDEX],
								arguments[UPDATE_NEW_LOCATION_INDEX],
								arguments[UPDATE_NEW_CREATION_TIME_INDEX],
								arguments[UPDATE_NEW_ACCESS_TIME_INDEX],
								arguments[UPDATE_NEW_FOOTAGE_INDEX]);
	}
	catch (std::exception& exception)
	{
		std::cout << exception.what() << '\n';
	}
}

void Interface::listAll(const std::vector<std::string>& arguments)
{
	if (m_currentAccess != InterfaceAccess::ADMIN)
	{
		throw std::exception("Must have admin privileges to view records!");
	}
	for (auto record = m_controller->begin(); record != m_controller->end(); record++)
	{
		printRecord(*(record->second.get()));
	}
}

void Interface::next(const std::vector<std::string> &arguments)
{
	auto iterator = m_controller->getListIterator();
	try
	{
		printRecord(*(iterator->second));
		m_controller->incrementListIterator();
	}
	catch (std::exception& exception)
	{
		std::cout << exception.what() << '\n';
	}
}

void Interface::save(const std::vector<std::string> &arguments)
{
	try
	{
		Record record = m_controller->getRecord(arguments[SAVE_TITLE_INDEX]);
		m_controller->saveRecord(record);
	}
	catch (std::exception& exception)
	{
		std::cout << exception.what() << '\n';
	}
}

void Interface::userList(const std::vector<std::string> &arguments)
{
	std::for_each(m_controller->userListBegin(), m_controller->userListEnd(), [this](const auto& record) { printRecord(record.second); });
}

void Interface::listTimesAccessed(const std::vector<std::string> &arguments)
{
	auto filterFunction = std::bind(filterTimesAccessed, std::placeholders::_1,
									arguments[LIST_TIMES_ACCESSED_LOCATION_INDEX],
									arguments[LIST_TIMES_ACCESSED_TIMES_ACCESSED_INDEX]);
	auto filteredRecords = m_controller->filter(filterFunction);
	std::for_each(filteredRecords.begin(), filteredRecords.end(), [this](const auto& record) { printRecord(record); });
}

void Interface::setFilepath(const std::vector<std::string> &arguments)
{
	try
	{
		m_controller->setFilepath(arguments[SET_FILEPATH_FILEPATH_INDEX]);
		m_controller->loadRecords();
	}
	catch (std::exception& exception)
	{
		std::cout << exception.what() << '\n';
	}
}

void Interface::printRecord(const Record& record) const
{
	std::cout << "Title: " << record.getTitle() << '\n';
	std::cout << "Location: " << record.getLocation() << '\n';
	std::cout << "Time of creation: " << record.getTimeOfCreation() << '\n';
	std::cout << "Access time: " << record.getTimeAccessed() << '\n';
	std::cout << "Footage preview: " << record.getFootagePreview() << '\n';
}
