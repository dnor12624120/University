#pragma once

#include <exception>

class InputException : public std::exception
{
	public:
		InputException(const char* message) :
			m_message(message)
		{

		}

		const char* what() const throw()
		{
			return m_message;
		} 
	private:
		const char* m_message;
};

class RepositoryException : public std::exception
{
	public:
		RepositoryException(const char* message) :
			m_message(message)
		{

		}

		const char* what() const throw()
		{
			return m_message;
		}
	private:
		const char* m_message;
};