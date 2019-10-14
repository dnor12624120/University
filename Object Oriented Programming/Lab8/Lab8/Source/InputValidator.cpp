#include "InputValidator.h"
#include "Interface.h"
#include "Exception.h"

#include <iostream>

InputValidator::InputValidator(const Interface& interface) :
	m_interface(interface)
{

}

void InputValidator::validateInput(const std::string& command, int argumentCount) const
{
	auto iterator = m_interface.m_commands.find(command);
	if (iterator == m_interface.m_commands.end())
	{
		throw InputException("No such command found!");
	}
	else
	{
		bool commandFound = false;
		while (iterator->first == command && iterator != m_interface.m_commands.end() && !commandFound)
		{
			if (iterator->second.argumentCount == argumentCount)
			{
				commandFound = true;
			}
			else
			{
				iterator++;
			}
		}
		if (!commandFound)
		{
			throw InputException("Invalid number of arguments!");
		}
	}
}