#include "MultiMap.h"
#include "MultiMapIterator.h"

#include <iostream>

/*
	Total Complexity: Theta(1)
*/
MultiMap::MultiMap():
	m_start(nullptr),
	m_end(nullptr),
	m_size(0)
{

}

/*
	Average Complexity: Theta(n)
	Best Case Complexity: Theta(1)
	Worst Case Complexity: Theta(n)
	Total Complexity: O(n)
*/
MultiMap::~MultiMap()
{
	Node* tempNode = m_start;
	while (m_start)
	{
		m_start = m_start->next;
		delete tempNode;
		tempNode = m_start;
	}
}

/*
	Average Complexity: Theta(n)
	Best Case Complexity: Theta(1)
	Worst Case Complexity: Theta(n)
	Total Complexity: O(n)
*/
void MultiMap::add(TKey c, TValue v)
{
	Node* tempNode = new Node(c, v);
	if (m_start == nullptr)
	{
		m_start = tempNode;
		m_end = tempNode;
		tempNode = nullptr;
	}
	else
	{
		m_end->next = tempNode;
		m_end = tempNode;
	}
	m_size++;
}

/*
	Average Complexity: Theta(n)
	Best Case Complexity: Theta(1)
	Worst Case Complexity: Theta(n)
	Total Complexity: O(n)
*/
bool MultiMap::remove(TKey c, TValue v)
{
	Node* tempNode = m_start;
	Node* prevNode = nullptr;

	if (tempNode && tempNode->data == std::make_pair(c, v))
	{
		m_start = tempNode->next;
		delete tempNode;
		m_size--;
		return true;
	}

	while (tempNode && tempNode->data != std::make_pair(c, v))
	{
		prevNode = tempNode;
		tempNode = tempNode->next;
	}

	if (tempNode == nullptr)
	{
		return false;
	}

	prevNode->next = tempNode->next;
	delete tempNode;
	m_size--;
	return true;
}

/*
	Average Complexity: Theta(n)
	Best Case Complexity: Theta(n)
	Worst Case Complexity: Theta(n)
	Total Complexity: Theta(n)
*/
vector<TValue> MultiMap::search(TKey c) const
{
	Node* tempNode = m_start;
	vector<TValue> values;
	while (tempNode)
	{
		if (tempNode->data.first == c)
		{
			values.emplace_back(tempNode->data.second);
		}
		tempNode = tempNode->next;
	}
	return values;	
}

/*
	Total Complexity: Theta(1)
*/
int MultiMap::size() const
{
	return m_size;
}

/*
	Total Complexity: Theta(1)
*/
bool MultiMap::isEmpty() const
{
	return m_size == 0;
}

/*
	Total Complexity: Theta(1)
*/
MultiMapIterator MultiMap::iterator() const
{
	return MultiMapIterator(*this);
}