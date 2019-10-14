#pragma once

#include <map>
#include <string>
#include <memory>

class Record;

class Repository
{
	public:
		Repository() = default;

		void addElement(const std::string& key, std::unique_ptr<Record> element);
		void removeElement(const std::string& key);
		void updateElement(const std::string& key, const std::string& newKey, std::unique_ptr<Record> newElement);
		Record* getRecord(const std::string& key);
		std::map<std::string, std::unique_ptr<Record>>::iterator iterator();
		std::map<std::string, std::unique_ptr<Record>>::iterator begin();
		std::map<std::string, std::unique_ptr<Record>>::iterator end();

	private:
		std::map<std::string, std::unique_ptr<Record>> m_elements;
};