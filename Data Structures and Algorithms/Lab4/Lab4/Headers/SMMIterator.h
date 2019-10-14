#pragma once

#include <utility>

typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
typedef bool(*Relation)(TKey, TKey);

class SortedMultiMap;

class SMMIterator
{
	public:
		void first();
		void next();
		void jumpBack(int k);
		bool valid() const;
		TElem getCurrent() const;
	private:
		friend class SortedMultiMap;
			
		SMMIterator(SortedMultiMap& c);
		SortedMultiMap& m_container;
		int m_index;
};


