#pragma once

#include <map>
#include <string>
#include <memory>

class Record;

class Repository
{
	public:
		/*
			Default constructor for the class.
		*/
		Repository() = default;

		/*
			Inserts a reference to the record with name key into the repository.
			Throws an exception if a record with the name key already exists in the repository.
		*/
		void addElement(const std::string& title, std::unique_ptr<Record> record);

		/*
			Removes a record with the name key from the repository.
			Throws an exception if no record named key exists in the repository.
		*/
		void removeElement(const std::string& title);

		/*
			Replaces the record with the name key from the repository with a new given one,
			named newKey.
			Throws an exception if a no record with the name key exists or
			a record with the name newKey already exists.
		*/
		void updateElement(const std::string& title, const std::string& newTitle, std::unique_ptr<Record> newRecord);

		/*
			Returns a copy of a record the name key.
		*/
		Record getRecord(const std::string& title);

		/*
			Returns an iterator to the repository (map).
		*/
		std::map<std::string, std::unique_ptr<Record>>::iterator iterator();

		/*
			Returns an iterator to the beginning of the repository (map).
		*/
		std::map<std::string, std::unique_ptr<Record>>::iterator begin();

		/*
			Returns an iterator to the end of the repository (map).
		*/
		std::map<std::string, std::unique_ptr<Record>>::iterator end();

		/*
			Returns a map of copies of the records whose location is location,
			and their accessTime is less than timesAccessed.
		*/
		std::map<std::string, Record> filterTimesAccessed(const std::string& location, const std::string& timesAccessed);

		/*
			Returns the number of elements in the map.
		*/
		inline const int size() const
		{
			return m_elements.size();
		}

	private:
		std::map<std::string, std::unique_ptr<Record>> m_elements;
};