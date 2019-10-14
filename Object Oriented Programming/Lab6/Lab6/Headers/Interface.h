#pragma once

#include "Controller.h"
#include "Record.h"

#include <memory>
#include <vector>
#include <string>
#include <functional>

enum InterfaceAccess
{
	DEFAULT,
	ADMIN,
	USER
};

class Interface
{
	public:
		struct Command
		{
			std::string name;
			int argumentCount;
			int index;
			
			Command() = default;

			Command(std::string n, int argc, int i):
				name(n), argumentCount(argc), index(i)
			{ }
		};

		/*
			Default constructor for the map.
		*/
		Interface() = default;

		/*
			Initializes interface with a reference to a controller.
		*/
		Interface(std::unique_ptr<Controller> controller);

		/*
			Main loop of the interface where commands are being read, parsed and executed.
		*/
		void run();

		/*
			Reads input from the user into string input until '\n'.
		*/
		void getInput(std::string& input);

		/*
			Parses a single input string into an array of strings, the first one being the command
			and the rest being the arguments, based on space delimiters.
		*/
		std::vector<std::string> parseInput(const std::string& input);

		/*
			Checks if a the given command exists and if so, that is has
			the correct number of arguments.
		*/
		bool validateInput(const std::string& command, int argumentCount);

		/*
			Returns the index within the internal function pointer list of
			the given command.
		*/
		int getCommandIndex(const std::string& command, int argumentCount);

		/*
			Function to exit from the interface.
		*/
		void exit(const std::vector<std::string> &arguments);

		/*
			Function to change the user to A/B.
		*/
		void changeAccess(const std::vector<std::string> &arguments);

		/*
			Function to add a record with the specified fields (arguments have descriptive indices
			with regard to what information they're containing).
				arguments[1] - title
				arguments[2] - location
				arguments[3] - timeOfCreation
				arguments[4] - timesAccessed
				arguments[5] - footagePreview
		*/
		void addRecord(const std::vector<std::string> &arguments);

		/*
			Function to add a record with the given key (arguments have descriptive indices
			with regard to what information they're containing).
				arguments[1] - title
		*/
		void removeRecord(const std::vector<std::string> &arguments);

		/*
			Updates a record with the new specified fields. (arguments have descriptive indices
			with regard to what information they're containing).
				arguments[1] - oldTitle
				arguments[2] - newTitle
				arguments[3] - newLocation
				arguments[4] - newTimeOfCreation
				arguments[5] - newTimesAccessed
				arguments[6] - newFootagePreview
		*/
		void updateRecord(const std::vector<std::string> &arguments);

		/*
			Lists all records currently in the repository.
		*/
		void listAll(const std::vector<std::string> &arguments);

		/*
			Prints the information of the next record of currently selected user. 
		*/
		void next(const std::vector<std::string> &arguments);

		/*
			Saves a record with the specified title to the personal list of a user. (arguments have descriptive indices
			with regard to what information they're containing).
				arguments[1] - title
		*/
		void save(const std::vector<std::string> &arguments);

		/*
			Lists the records saved to the personal list of the current user.
		*/
		void userList(const std::vector<std::string> &arguments);

		/*
			Lists all records whose location is a given location and the number of 
			times they were accessed is less than a given access time. (arguments have descriptive indices
			with regard to what information they're containing).
				arguments[1] - location
				arguments[2] - accessTime to compare
		*/
		void listTimesAccessed(const std::vector<std::string> &arguments);

		/*
			Formatted print of a record.
		*/
		void printRecord(const Record& record) const;

	private:
		std::unique_ptr<Controller> m_controller;
		std::multimap<std::string, Command> m_commands;
		std::vector<std::function<void(const std::vector<std::string>)>> m_functions;
		bool m_running;
		InterfaceAccess m_currentAccess;
		
};