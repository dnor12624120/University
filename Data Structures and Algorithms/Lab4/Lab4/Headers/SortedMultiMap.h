#pragma once

#include "DLLA.h"

#include <vector>
#include <utility>

using namespace std;

typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
typedef bool(*Relation)(TKey, TKey);

class SMMIterator;

class SortedMultiMap
{
	public:
		SortedMultiMap(Relation r);
		~SortedMultiMap();
		void add(TKey c, TValue v);
		vector<TValue> search(TKey c) const;
		bool remove(TKey c, TValue v);
		int size() const;
		bool isEmpty() const;
		SMMIterator iterator();
		void print() const;
	public:
		const inline int firstIndex() const
		{
			return m_elements.head();
		}
		friend class SMMIterator;
		
		DLLA m_elements;
		Relation m_relation;
};
