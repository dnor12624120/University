#pragma once

#include <map>
#include <string>

template<typename Key, typename Object>
class UserList
{
	public:
		UserList() = default;
		
		virtual void setFilepath(const std::string& filepath) = 0;
		virtual void loadAll() = 0;
		virtual void addObject(const Key& key, const Object& object) = 0;
		
		inline const std::string& getFilepath() const { return m_filepath; }
		inline typename std::map<Key, Object>::iterator begin() { return m_list.begin(); }
		inline typename std::map<Key, Object>::iterator end() { return m_list.end(); }
	protected:
		std::string m_filepath;
		std::map<Key, Object> m_list;
		typename std::map<Key, Object>::iterator m_iterator;
};