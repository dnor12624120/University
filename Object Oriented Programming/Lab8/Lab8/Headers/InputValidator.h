#pragma once

#include <string>

class Interface;

class InputValidator
{
	public:
		InputValidator() = default;
		InputValidator(const Interface& interface);

		void validateInput(const std::string& command, int argumentCount) const;
	private:
		friend class Inteface;

		const Interface& m_interface;
};