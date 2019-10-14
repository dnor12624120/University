#include "MultiMapIterator.h"
#include "MultiMap.h"

#include <exception>

/*
	Total Complexity: Theta(1)
*/
MultiMapIterator::MultiMapIterator(const MultiMap& c):
	m_container(c),
	m_current(c.m_start)
{

}

/*
	Total Complexity: Theta(1)
*/
void MultiMapIterator::first()
{
	m_current = m_container.m_start;
}

/*
	Total Complexity: Theta(1)
*/
void MultiMapIterator::next()
{
	if (m_current == nullptr)
	{
		throw std::exception("Invalid iterator!");
	}
	m_current = m_current->next;
}

/*
	Total Complexity: Theta(1)
*/
bool MultiMapIterator::valid() const
{
	return m_current != nullptr;
}

/*
	Total Complexity: Theta(1)
*/
TElem MultiMapIterator::getCurrent() const
{
	return m_current->data;
}


