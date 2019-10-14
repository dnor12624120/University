#pragma once

#include <utility>
#include <stack>

typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
typedef bool(*Relation)(TKey, TKey);

class SortedMultiMap;

using namespace std;

class SMMIterator
{
	public:
		/*
			Total Complexity: Theta(1)
		*/
		void first();

		/*
			Total Complexity: Theta(n)
			Best Case: Theta(1)
			Worst Case: Theta(n)
			Average Complexity: O(n)
		*/
		void next();

		/*
			Total Complexity: Theta(1)
		*/
		bool valid() const;

		/*
			Total Complexity: Theta(1)
		*/
		TElem getCurrent() const;
	private:
		friend class SortedMultiMap;

		/*
			Total Complexity: Theta(n)
			Best Case: Theta(1)
			Worst Case: Theta(n)
			Average Complexity: O(n)
		*/
		SMMIterator(const SortedMultiMap& map);

		const SortedMultiMap& m_map;
		stack<int> m_stack;
		int m_current;
};


