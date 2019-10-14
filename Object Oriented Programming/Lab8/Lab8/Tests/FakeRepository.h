#pragma once

#include "Repository.h"
#include "Record.h"

#include <string>
#include <memory>

template<typename Key, typename Object>
class FakeRepository : public Repository<Key, Object>
{
	public:
		FakeRepository() = default;

		void addObject(const Key& key, std::unique_ptr<Object> object) override
		{

		}

		void removeObject(const Key& key) override
		{

		}

		Object getObject(const Key& key) override
		{
			return Object();
		}

		typename std::map<Key, std::unique_ptr<Object>>::iterator iterator() override
		{
			return std::map<Key, std::unique_ptr<Object>>::iterator();
		}

		typename std::map<Key, std::unique_ptr<Object>>::iterator begin() override
		{
			return std::map<Key, std::unique_ptr<Object>>::iterator();
		}

		typename std::map<Key, std::unique_ptr<Object>>::iterator end() override
		{
			return std::map<Key, std::unique_ptr<Object>>::iterator();
		}

		std::vector<Object> filter(const std::function<bool(Object*)>& filterFunction) override
		{
			return std::vector<Object>();
		}

		inline const int size() const override
		{
			return 0;
		}

		void clear() override
		{

		}
};