#include "Heap.h"

#include <iostream>
#include <algorithm>
#include <utility>

/*
	Total Complexity: Theta(1)
*/
Heap::Heap(Relation relation):
	m_size(0),
	m_capacity(DEFAULT_CAPACITY),
	m_relation(relation)
{
	m_elements = new std::pair<int, int>[m_capacity];
}

/*
	Total Complexity: Theta(1)
*/
Heap::~Heap()
{
	delete[] m_elements;
}

/*
	Average Complexity: Theta(log4(n))
	Best Case: Theta(1)
	Worst Case: Theta(log4(n))
	Total Complexity: O(log4(n))
*/
void Heap::push(const std::pair<int, int>& value)
{
	if (m_size == m_capacity)
	{
		resize();
	}
	m_elements[m_size++] = value;
	int index = m_size - 1;
	while (index != 0 && m_relation(m_elements[index].second, m_elements[(index - 1) / 4].second))
	{
		std::swap(m_elements[index], m_elements[(index - 1) / 4]);
		index = (index - 1) / 4;
	}
}

/*
	Total Complexity: Theta(1)
*/
const std::pair<int, int>& Heap::top() const
{
	return m_elements[0];
}

/*
	Average Complexity: Theta(log4(n))
	Best Case: Theta(1)
	Worst Case: Theta(log4(n))
	Total Complexity: O(log4(n))
*/
void Heap::pop()
{
	std::swap(m_elements[0], m_elements[m_size - 1]);
	m_size--;
	int swappedIndex = 0;
	bool swapping = true;
	while (swapping)
	{
		swapping = false;
		int child1 = 4 * swappedIndex + 1;
		int child2 = 4 * swappedIndex + 2;
		int child3 = 4 * swappedIndex + 3;
		int child4 = 4 * swappedIndex + 4;
		int min = swappedIndex;
		bool valid = false;
		if (validIndex(child1))
		{
			valid = true;
			min = child1;
		}
		if (validIndex(child1) && validIndex(child2))
		{
			valid = true;
			min = m_relation(m_elements[child1].second, m_elements[child2].second) ? child1 : child2;
		}
		if (validIndex(child2) && validIndex(child3))
		{
			valid = true;
			min = m_relation(m_elements[min].second, m_elements[child3].second) ? min : child3;
		}
		if (validIndex(child3) && validIndex(child4))
		{
			valid = true;
			min = m_relation(m_elements[min].second, m_elements[child4].second) ? min : child4;
		}
		if (m_relation(m_elements[min].second, m_elements[swappedIndex].second))
		{
			swapping = true;
			std::swap(m_elements[min], m_elements[swappedIndex]);
		}
		swappedIndex = min;
		if (!valid)
		{
			break;
		}
	}
}

/*
	Average Complexity: Theta(n)
	Best Case: Theta(1)
	Worst Case: Theta(n)
	Total Complexity: O(n)
*/
int Heap::search(int value)
{
	for (int i = 0; i < m_size; i++)
	{
		if (m_elements[i].first == value)
		{
			return i;
		}
	}
	return -1;
}

/*
	Total Complexity: O(n)
*/
void Heap::resize()
{
	std::pair<int, int>* tempElements = new std::pair<int, int>[m_capacity * 2];
	for (int i = 0; i < m_size; i++)
	{
		tempElements[i] = m_elements[i];
	}
	delete[] m_elements;
	m_elements = tempElements;
	m_capacity *= 2;
}
