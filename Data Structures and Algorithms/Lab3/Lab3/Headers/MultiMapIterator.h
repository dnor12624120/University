#pragma once

#include <utility>

class MultiMap;
class Node;
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;

class MultiMapIterator
{
	public:
		void first();
		void next();
		bool valid() const;
		TElem getCurrent() const;
	private:
		friend class MultiMap;

		MultiMapIterator(const MultiMap& c);
		const MultiMap& m_container;
		Node* m_current;
};