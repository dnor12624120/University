#pragma once

#include "Repository.h"

#include <iostream>
#include <string>

template<typename Key, typename Object>
class CVSRepository : public Repository<Key, Object>
{
	public:
		/*
			Default constructor for CVSRepostiory.
		*/
		CVSRepository();

		/*
			Constructor for CVSRepository that takes a string of the filepath where data will be stored.
		*/
		CVSRepository(const std::string& filepath);

		/*

		*/
		void setFilepath(const std::string& filepath);


		/*

		*/
		void loadObjects();

		/*
			Inserts a reference to an object with the key key into the repository.
			Throws an exception if an object with the key key already exists in the repository.
		*/
		void addObject(const Key& key, std::unique_ptr<Object> object) override;

		/*
			Removes an object with the key key from the repository.
			Throws an exception if no object with the key key exists in the repository.
		*/
		void removeObject(const Key& key) override;
	private:
		std::string m_filepath;
};