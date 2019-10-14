#include "DLLAIterator.h"
#include "DLLA.h"

#include <exception>

/*
	Total Complexity: Theta(1)
*/
DLLAIterator::DLLAIterator(const DLLA& c):
	m_container(c),
	m_index(c.m_head)
{

}

/*
	Total Complexity: Theta(1)
*/
void DLLAIterator::first()
{
	m_index = m_container.m_head;
}

/*
	Total Complexity: Theta(1)
*/
void DLLAIterator::next()
{
	if (!valid())
	{
		throw std::exception("Invalid iterator!");
	}
	m_index = m_container.m_elements[m_index].next;
}

/*
	Total Complexity: Theta(1)
*/
bool DLLAIterator::valid() const
{
	return m_index != -1;
}

/*
	Average Complexity: Theta(n)
	Best Case: Theta(1)
	Worst Case: Theta(n)
	Total Complexity: O(n)
*/
TElem DLLAIterator::getCurrent() const
{
	return m_container.m_elements[m_index].pair;
}