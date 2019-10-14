#include "PriorityQueue.h"

#include <exception>
#include <iostream>

/*
	Total Complexity: Theta(1)
*/
PriorityQueue::PriorityQueue(Relation r):
	m_elements(Heap(r))
{

}

/*
	Total Complexity: Theta(1)
*/
PriorityQueue::~PriorityQueue()
{

}

/*
	Average Complexity: Theta(log4(n))
	Best Case: Theta(1)
	Worst Case: Theta(log4(n))
	Total Complexity: O(log4(n))
*/
void PriorityQueue::push(TElem e, TPriority p)
{
	m_elements.push(std::make_pair(e, p));
}

/*
	Total Complexity: Theta(1)
*/
Element PriorityQueue::top() const
{
	if (isEmpty())
	{
		throw std::exception("Priority queue is empty!");
	}
	return m_elements.top();
}

/*
	Average Complexity: Theta(log4(n))
	Best Case: Theta(1)
	Worst Case: Theta(log4(n))
	Total Complexity: O(log4(n))
*/
Element PriorityQueue::pop()
{
	if (isEmpty())
	{
		throw std::exception("Priority queue is empty!");
	}
	auto top = m_elements.top();
	m_elements.pop();
	return top;
}

/*
	Total Complexity: Theta(1)
*/
bool PriorityQueue::isEmpty() const
{
	return m_elements.size() == 0;
}
