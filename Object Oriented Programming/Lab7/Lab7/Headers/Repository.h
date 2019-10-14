#pragma once

#include <map>
#include <string>
#include <memory>
#include <vector>
#include <functional>

class Record;

template<typename Key, typename Object>
class Repository
{
	public:
		/*
			Default constructor for the class.
		*/
		Repository() = default;

		/*
			Inserts a reference to an object with the key key into the repository.
			Throws an exception if an object with the key key already exists in the repository.
		*/
		virtual void addObject(const Key& key, std::unique_ptr<Object> object);

		/*
			Removes an object with the key key from the repository.
			Throws an exception if no object with the key key exists in the repository.
		*/
		virtual void removeObject(const Key& key);

		/*
			Returns a copy of an object with the key key.
		*/
		Object getObject(const Key& key);

		/*
			Returns an iterator to the repository (map).
		*/
		typename std::map<Key, std::unique_ptr<Object>>::iterator iterator();

		/*
			Returns an iterator to the beginning of the repository (map).
		*/
		typename std::map<Key, std::unique_ptr<Object>>::iterator begin();

		/*
			Returns an iterator to the end of the repository (map).
		*/
		typename std::map<Key, std::unique_ptr<Object>>::iterator end();

		/*
			Returns a map of copies of the records whose location is location,
			and their accessTime is less than timesAccessed.
		*/
		std::vector<Object> filter(const std::function<bool(Object*)>& filterFunction);

		/*
			Returns the number of objects in the map.
		*/
		inline const int size() const
		{
			return m_elements.size();
		}

		void clear();

	protected:
		std::map<Key, std::unique_ptr<Object>> m_elements;
};