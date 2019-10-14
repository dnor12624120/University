#pragma once

#include <vector>
#include <utility>

using namespace std;

class MultiMapIterator;

typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;

struct Node
{
	TElem data;
	Node* next;

	/*
		Total Complexity: Theta(1)
	*/
	Node(TKey key, TValue value) :
		data(std::make_pair(key, value)),
		next(nullptr)
	{

	}
};

class MultiMap
{
	public:
		MultiMap();
		~MultiMap();

		void add(TKey c, TValue v);
		bool remove(TKey c, TValue v);
		vector<TValue> search(TKey c) const;
		int size() const;
		bool isEmpty() const;
		MultiMapIterator iterator() const;
	private:
		friend class MultiMapIterator;
		
		Node* m_start;
		Node* m_end;	
		unsigned int m_size;
};


	