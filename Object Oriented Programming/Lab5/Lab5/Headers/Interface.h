#pragma once

#include "Controller.h"
#include "Record.h"

#include <memory>
#include <vector>
#include <string>
#include <functional>


class Interface
{
	public:
		enum InterfaceAccess
		{
			DEFAULT,
			ADMIN,
			USER
		};

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

		Interface() = default;
		Interface(std::unique_ptr<Controller> controller);

		void run();
		void getInput(std::string& input);
		std::vector<std::string> parseInput(const std::string& input);
		bool validateInput(const std::string& command, int argumentCount);
		int getCommandIndex(const std::string& command);
		void setAccess();

		void exit(const std::vector<std::string> &arguments);
		void changeAccess(const std::vector<std::string> &arguments);
		void addRecord(const std::vector<std::string> &arguments);
		void removeRecord(const std::vector<std::string> &arguments);
		void updateRecord(const std::vector<std::string> &arguments);
		void listAll(const std::vector<std::string> &arguments);

		void printRecord(const Record& record) const;

	private:
		std::unique_ptr<Controller> m_controller;
		std::map<std::string, Command> m_commands;
		std::vector<std::function<void(const std::vector<std::string>)>> m_functions;
		bool m_running;
		InterfaceAccess m_currentAccess;
		
};