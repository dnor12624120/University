#include "Interface.h"

#include <iostream>
#include <sstream>
#include <algorithm>

#define NUM_OF_FUNCTIONS 6

#define EXIT_INDEX 0
#define MODE_INDEX 1
#define ADD_INDEX 2
#define UPDATE_INDEX 3
#define DELETE_INDEX 4
#define LIST_ALL_INDEX 5

#define EXIT_ARGUMENT_COUNT 0
#define MODE_ARGUMENT_COUNT 1
#define ADD_ARGUMENT_COUNT 5
#define UPDATE_ARGUMENT_COUNT 5
#define DELETE_ARGUMENT_COUNT 1
#define LIST_ALL_ARGUMENT_COUNT 0

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

static const bool isStringNumeric(const std::string& argument)
{
	for (int i = 0; i < argument.length(); i++)
	{
		if (argument[i] < '0' && argument[i] > '9')
		{
			return false;
		}
	}
	return true;
}

static const bool isValidDate(const std::string& date)
{
	return 
		isStringNumeric(date.substr(0, 2)) && isStringNumeric(date.substr(3, 2)) && isStringNumeric(date.substr(6, 4));
}

Interface::Interface(std::unique_ptr<Controller> controller):
	m_controller(std::move(controller)),
	m_running(true),
	m_currentAccess(InterfaceAccess::ADMIN)
{
	// initialize command vector
	m_commands.insert(std::make_pair<std::string, Command>("exit", Command("exit", EXIT_ARGUMENT_COUNT, EXIT_INDEX)));
	m_commands.insert(std::make_pair<std::string, Command>("mode", Command("mode", MODE_ARGUMENT_COUNT, MODE_INDEX)));
	m_commands.insert(std::make_pair<std::string, Command>("add", Command("add", ADD_ARGUMENT_COUNT, ADD_INDEX)));
	m_commands.insert(std::make_pair<std::string, Command>("update", Command("update", UPDATE_ARGUMENT_COUNT, UPDATE_INDEX)));
	m_commands.insert(std::make_pair<std::string, Command>("delete", Command("delete", DELETE_ARGUMENT_COUNT, DELETE_INDEX)));
	m_commands.insert(std::make_pair<std::string, Command>("list", Command("list", LIST_ALL_ARGUMENT_COUNT, LIST_ALL_INDEX)));
	// initialize function pointer vector
	m_functions.resize(NUM_OF_FUNCTIONS);
	m_functions[EXIT_INDEX] = std::bind(&Interface::exit, this, std::placeholders::_1);
	m_functions[MODE_INDEX] = std::bind(&Interface::changeAccess, this, std::placeholders::_1);
	m_functions[ADD_INDEX] = std::bind(&Interface::addRecord, this, std::placeholders::_1);
	m_functions[UPDATE_INDEX] = std::bind(&Interface::updateRecord, this, std::placeholders::_1);
	m_functions[DELETE_INDEX] = std::bind(&Interface::removeRecord, this, std::placeholders::_1);
	m_functions[LIST_ALL_INDEX] = std::bind(&Interface::listAll, this, std::placeholders::_1);
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
			validateInput(arguments[0], arguments.size() - 1);
			int index = getCommandIndex(arguments[0]);
			m_functions[index](arguments);
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << '\n';
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

	while (std::getline(stringstreamInput, argument, ' '))
	{
		arguments.emplace_back(argument);
	}

	for (int i = 0; i < arguments.size(); i++)
	{
		if (arguments[i][arguments[i].length() - 1] == ',')
		{
			arguments[i].erase(arguments[i].length() - 1, 1);
		}
	}

	return arguments;
}

bool Interface::validateInput(const std::string& command, int argumentCount)
{
	auto iterator = m_commands.find(command);
	if (iterator == m_commands.end())
	{
		throw std::exception("No such command found!");
	}
	else
	{
		if (iterator->second.argumentCount != argumentCount)
		{
			throw std::exception("Invalid number of arguments!");
		}
	}
	return true;
}

int Interface::getCommandIndex(const std::string& command)
{
	return m_commands[command].index;
}

void Interface::setAccess()
{
	std::string input;
	std::cout << "Enter an access mode: \n";
	getInput(input);
	while (input != "A" && input != "B")
	{
		std::cout << "Invalid access mode!\n";
		getInput(input);
	}
	m_currentAccess = input == "A" ? InterfaceAccess::ADMIN : InterfaceAccess::USER;
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
	catch (std::exception& e)
	{
		std::cout << e.what() << '\n';
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
	catch (std::exception& e)
	{
		std::cout << e.what() << '\n';
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
	catch (std::exception& e)
	{
		std::cout << e.what() << '\n';
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

void Interface::printRecord(const Record& record) const
{
	std::cout << "Title: " << record.getTitle() << '\n';
	std::cout << "Location: " << record.getLocation() << '\n';
	std::cout << "Time of creation: " << record.getTimeOfCreation() << '\n';
	std::cout << "Access time: " << record.getTimeAccessed() << '\n';
	std::cout << "Footage preview: " << record.getFootagePreview() << '\n';
}
