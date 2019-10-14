#include "SortedBagIterator.h"

#include <exception>

/*
	Total Complexity: Theta(1)
*/
SortedBagIterator::SortedBagIterator(const SortedBag& sortedBag) :
	m_container(sortedBag),
	m_index(sortedBag.size()),
	m_valid(sortedBag.size())
{ }

/*
	Total Complexity: Theta(1)
*/
void SortedBagIterator::first()
{
	if (m_container.size() == 0)
	{
		m_valid = false;
	}
	m_index = 0;
	m_valid = true;
}

/*
	Total Complexity: Theta(1)
*/
void SortedBagIterator::next()
{
	if (!m_valid)
	{
		throw std::exception("Invalid iterator!");
	}
	if (m_index == m_container.size())
	{
		m_valid = false;
		m_index = -1;
	}
	else
	{
		m_index++;
	}
}

/*
	Total Complexity: Theta(1)
*/
bool SortedBagIterator::valid() const
{
	return m_valid;
}

/*
	Total Complexity: Theta(1)
*/
TElem SortedBagIterator::getCurrent() const
{
	if (!m_valid)
	{
		throw std::exception("Invalid iterator!");
	}
	return m_container.m_elements[m_index];
}