#pragma once

#include "UserList.h"

template<typename Key, typename Object>
class CVSUserList : public UserList<Key, Object>
{
	public:
		CVSUserList() = default;

		void setFilepath(const std::string& filepath) override;
		void loadAll() override;
		void addObject(const Key& key, const Object& object) override;
};
