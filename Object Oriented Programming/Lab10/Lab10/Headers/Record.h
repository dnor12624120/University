#pragma once

#include <string>
#include <iostream>

class Record
{
	public:
		/*
			Default constructor for the map.
		*/
		Record() = default;

		/*
			Constructor that initializes record with the given values.
		*/
		Record(const std::string& title, const std::string& location, const std::string& timeOfCreation,
			   const std::string& timeAccessed, const std::string& footagePreview);

		/*
			Constructor that copies the fields of the given pointer.
		*/
		Record(Record* record);

		/*
			Returns title of the record.
		*/
		inline const std::string& getTitle() const
		{
			return m_title;
		}

		/*
			Returns title of the record.
		*/
		inline const std::string& getLocation() const
		{
			return m_location;
		}

		/*
			Returns creation time of the record.
		*/
		inline const std::string& getTimeOfCreation() const
		{
			return m_timeOfCreation;
		}

		/*
			Returns the number of times the record was accessed.
		*/
		inline const std::string& getTimeAccessed() const
		{
			return m_timeAccessed;
		}

		/*
			Returns footage preview of the record.
		*/
		inline const std::string& getFootagePreview() const
		{
			return m_footagePreview;
		}

		/*
			Sets the title of the record.
		*/
		void setTitle(const std::string& title);

		/*
			Sets the location of the record.
		*/
		void setLocation(const std::string& location);

		/*
			Sets the creation time of the record.
		*/
		void setTimeOfCreation(const std::string& timeOfCreation);

		/*
			Sets the number of access times of the record.
		*/
		void setTimeAccessed(const std::string& timeAccessed);

		/*
			Sets the footage preview of the record.
		*/
		void setFootagePreview(const std::string& footagePreview);

		/*
			Overloads the istream operator for the class.
		*/
		friend std::istream& operator>>(std::istream& inputStream, Record& record);

		/*
			Overloads the ofstream operator for the class.
		*/
		friend std::ostream& operator<<(std::ostream& outputStream, const Record& record);

		/*
			Overloads the equality operator on the class, checking for equality with regard to its string members.
		*/
		inline bool operator==(const Record& otherRecord)
		{
			return m_title == otherRecord.m_title &&
				m_location == otherRecord.m_location &&
				m_timeOfCreation == otherRecord.m_timeOfCreation &&
				m_timeAccessed == otherRecord.m_timeAccessed &&
				m_footagePreview == otherRecord.m_footagePreview;
		}
	private:
		std::string m_title;
		std::string m_location;
		std::string m_timeOfCreation;
		std::string m_timeAccessed;
		std::string m_footagePreview;
};