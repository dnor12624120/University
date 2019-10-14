#include "SMMIterator.h"
#include "SortedMultiMap.h"

#include <exception>
#include <iostream>

/*
	Total Complexity: Theta(1)
*/
SMMIterator::SMMIterator(SortedMultiMap& c):
	m_container(c),
	m_index(0)
{

}

/*
	Total Complexity: Theta(1)
*/
void SMMIterator::first()
{
	m_index = 0;
}

/*
	Total Complexity: Theta(1)
*/
void SMMIterator::next()
{
	if (!valid())
	{
		throw std::exception("Invalid iterator!");
	}
	m_index++;
}

/*
	Average Complexity: Theta(n)
	Best Case: Theta(1)
	Worst Case: Theta(n)
	Total Complexity: O(n)
*/
void SMMIterator::jumpBack(int k)
{
	if (!valid())
	{
		throw std::exception("Invalid iterator!");
	}
	if (m_index - k >= 0 && k)
	{
		m_index -= k;
	}
}

/*
	Total Complexity: Theta(1)
*/
bool SMMIterator::valid() const
{
	return m_index < m_container.size() && m_index >= 0;
}

/*
	Average Complexity: Theta(n)
	Best Case: Theta(1)
	Worst Case: Theta(n)
	Total Complexity: O(n)
*/
TElem SMMIterator::getCurrent() const
{
	return m_container.m_elements[m_index].pair;
}