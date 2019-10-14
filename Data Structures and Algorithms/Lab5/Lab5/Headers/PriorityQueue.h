#pragma once
#include <utility>

#include "Heap.h"

using namespace std;

typedef int TElem;
typedef int TPriority;
typedef std::pair<TElem, TPriority> Element;
typedef bool(*Relation)(TPriority p1, TPriority p2);

class PriorityQueue 
{
	public:
		PriorityQueue(Relation r);
		void push(TElem e, TPriority p);
		Element top()  const;
		Element pop();
		bool isEmpty() const;
		void print() const;
		~PriorityQueue();
	private:
		Heap m_elements;
		Relation m_relation;
};