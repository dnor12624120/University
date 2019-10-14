#pragma once

#include <string>

class Record
{
	public:
		Record() = default;
		Record(const std::string& title, const std::string& location, const std::string& timeOfCreation,
			   const std::string& timeAccessed, const std::string& footagePreview);

		inline const std::string& getTitle() const
		{
			return m_title;
		}

		inline const std::string& getLocation() const
		{
			return m_location;
		}

		inline const std::string& getTimeOfCreation() const
		{
			return m_timeOfCreation;
		}

		inline const std::string& getTimeAccessed() const
		{
			return m_timeAccessed;
		}

		inline const std::string& getFootagePreview() const
		{
			return m_footagePreview;
		}

		void setTitle(const std::string& title);
		void setLocation(const std::string& location);
		void setTimeOfCreation(const std::string& timeOfCreation);
		void setTimeAccessed(const std::string& timeAccessed);
		void setFootagePreview(const std::string& footagePreview);

	private:
		std::string m_title;
		std::string m_location;
		std::string m_timeOfCreation;
		std::string m_timeAccessed;
		std::string m_footagePreview;
};