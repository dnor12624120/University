#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& map):
	m_map(map)
{
	int index = m_map.m_root;
	while (index != -1)
	{
		m_stack.push(index);
		index = m_map.m_elements[index].left;
	}
	!m_stack.empty() ? m_current = m_stack.top() : m_current = -1;
}

void SMMIterator::first()
{
	!m_stack.empty() ? m_current = m_stack.top() : m_current = -1;
}

void SMMIterator::next()
{
	if (!valid())
	{
		throw std::exception("Iterator out of range!");
	}
	int index = m_stack.top();
	m_stack.pop();
	if (m_map.m_elements[index].right != -1)
	{
		index = m_map.m_elements[index].right;
		while (index != -1)
		{
			m_stack.push(index);
			index = m_map.m_elements[index].left;
		}
	}
	!m_stack.empty() ? m_current = m_stack.top() : m_current = -1;
}

bool SMMIterator::valid() const
{
	return m_current != -1;
}

TElem SMMIterator::getCurrent() const
{
	if (!valid())
	{
		throw std::exception("Iterator out of range!");
	}
	return m_map.m_elements[m_current].pair;
}

