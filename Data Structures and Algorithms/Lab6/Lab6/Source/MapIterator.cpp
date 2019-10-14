#include "MapIterator.h"
#include "Map.h"

#include <exception>

MapIterator::MapIterator(const Map& map) :
	m_map(map)
{
	m_current = 0;
	while (!m_map.m_elements[m_current].used)
	{
		m_current++;
	}
}

void MapIterator::first()
{
	m_current = 0;
	while (!m_map.m_elements[m_current].used)
	{
		m_current++;
	}
}

void MapIterator::next()
{
	if (!valid())
	{
		throw std::exception("Invalid iterator!");
	}
	while (!m_map.m_elements[++m_current].used && valid())
	{
		
	}
}

bool MapIterator::valid() const
{
	return m_current < m_map.m_capacity;
}

TElem MapIterator::getCurrent() const
{
	if (!valid())
	{
		throw std::exception("Invalid iterator!");
	}
	return m_map.m_elements[m_current].pair;
}