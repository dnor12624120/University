#pragma once

#include "Repository.h"
#include "Record.h"
#include "UserList.h"

#include <memory>
#include <vector>

class Record;
enum InterfaceAccess;

class Controller
{
	public:
		/*
			Default constructor for the class.
		*/
		Controller() = default;

		/*
			Initialized controller with a reference to a repository.
		*/
		Controller(std::unique_ptr<Repository<std::string, Record>> repository);

		/*
			Adds a record with the given fields to the local repository.
		*/
		void addRecord(const std::string& title, const std::string& location, const std::string& timeOfCreation,
					   const std::string& timeAccessed, const std::string& footagePreview);

		/*
			Updatse a record with thr new given fields from the local repository.
		*/
		void updateRecord(const std::string& title, const std::string& newLocation,
						  const std::string& newTimeOfCreation, const std::string& newTimeAccessed,
						  const std::string& newFootagePreview);

		/*
			Deletes a record with the given title from the local repository.
		*/
		void deleteRecord(const std::string& title);

		/*
			Returns a copy of a record from the local repository.
		*/
		Record getRecord(const std::string& title) const;

		/*
			Returns an iterator to the local repository.
		*/
		std::map<std::string, std::unique_ptr<Record>>::iterator iterator();

		/*
			Returns an iterator to the beginning of the repository.
		*/
		std::map<std::string, std::unique_ptr<Record>>::iterator begin();

		/*
			Returns an iterator to the end of the repository.
		*/
		std::map<std::string, std::unique_ptr<Record>>::iterator end();

		/*
			Returns an iterator the the personal list of user A/B.
		*/
		std::map<std::string, std::unique_ptr<Record>>::iterator getListIterator();

		/*
			Increments the iterator of the personal list of user A/B.
		*/
		void incrementListIterator();

		/*
			Saves a record to the personal list of user A/B.
		*/
		void saveRecord(const Record& record);

		/*
			Returns an iterator to the personal list of user A/B.
		*/
		std::map<std::string, Record>::iterator userListIterator();

		/*
			Returns an iterator to the beginning of the personal list of user A/B.
		*/
		std::map<std::string, Record>::iterator userListBegin();

		/*
			Returns an iterator to the end of the personal list of user A/B.
		*/
		std::map<std::string, Record>::iterator userListEnd();

		/*
			Returns a list of records whose location is location and accessTime is less than timesAccessed.
		*/
		std::vector<Record> filter(std::function<bool(Record*)> filterFunction);

		/*
			Sets the current user to be the one currently selected in the interface (A/B).
		*/
		void setUser(InterfaceAccess access);

		/*

		*/
		void setFilepath(const std::string& filepath);

		/*

		*/
		void loadRecords();

		/*
		
		*/
		void setUserListFilepath(const std::string& filepath);

		/*
		
		*/
		void setAdminListFilepath(const std::string& filepath);

		/*
		
		*/
		void loadUserListObjects();

		/*
		
		*/
		void loadAdminListObjects();

		/*
		
		*/
		void openUserList();

	private:
		std::unique_ptr<Repository<std::string, Record>> m_repository;
		std::unique_ptr<UserList<std::string, Record>> m_userList;
		std::unique_ptr<UserList<std::string, Record>> m_adminList;
		std::map<std::string, std::unique_ptr<Record>>::iterator m_userIterator;
		std::map<std::string, std::unique_ptr<Record>>::iterator m_adminIterator;
		InterfaceAccess m_currentUser;
};