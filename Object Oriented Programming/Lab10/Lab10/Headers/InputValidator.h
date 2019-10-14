#pragma once

#include <string>
#include <exception>

class InputValidator
{
	public:
		void validateTitle(const std::string& title)
		{
			if (isEmpty(title))
			{
				throw std::exception("No string entered for title!");
			}
		}

		void validateLocation(const std::string& location)
		{
			if (isEmpty(location))
			{
				throw std::exception("No string entered for location!");
			}
		}

		void validateTimeOfCreation(const std::string& timeOfCreation)
		{
			if (isEmpty(timeOfCreation))
			{
				throw std::exception("No string entered for time of creation!");
			}
			if (!isValidDate(timeOfCreation))
			{
				throw std::exception("Entered string is not in a valid format!");
			}
		}

		void validateAccessTime(const std::string& accessTime)
		{
			if (isEmpty(accessTime))
			{
				throw std::exception("No string entered for access time!");
			}
			if (!isNumeric(accessTime))
			{
				throw std::exception("Entered string is not numeric!");
			}
		}

		void validateFootagePreview(const std::string& footagePreview)
		{
			if (isEmpty(footagePreview))
			{
				throw std::exception("No string entered for footage preview!");
			}
		}
	private:
		bool isEmpty(const std::string& field)
		{
			return field.length() == 0;
		}

		bool isValidDate(const std::string& field)
		{
			return
				isNumeric(field.substr(0, 2)) && isNumeric(field.substr(3, 2)) && isNumeric(field.substr(6, 4));
		}

		bool isNumeric(const std::string& field)
		{
			for (int i = 0; i < field.length(); i++)
			{
				if (!isdigit(field[i]))
				{
					return false;
				}
			}
			return true;
		}
};