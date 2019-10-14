#pragma once

#include <exception>
#include <string>

class WinSockException : public std::exception
{
	public:
		WinSockException(const std::string& message) :
			exception{ message.c_str() }
		{

		}
};