#include "Map.h"
#include "MapIterator.h"

#include <iostream>

#define DEFAULT_VALUE INT_MIN
#define DEFAULT_CAPACITY 13 

Map::Map():
	m_size(0),
	m_capacity(DEFAULT_CAPACITY),
	m_elements(nullptr),
	m_firstFree(0)
{
	m_elements = new Element[m_capacity];
	for (int i = 0; i < m_capacity; i++)
	{
		m_elements[i].used = false;
		m_elements[i].next = -1;
		m_elements[i].pair = std::make_pair(DEFAULT_VALUE, DEFAULT_VALUE);
	}
}

Map::~Map()
{
	delete[] m_elements;
}

TValue Map::add(TKey c, TValue v)
{
	if (m_size == m_capacity)
	{
		resize();
	}
	int pos = hash(c, m_capacity);
	if (m_elements[pos].used == true && m_elements[pos].pair.first == c)
	{
		int oldValue = m_elements[pos].pair.second;
		m_elements[pos].pair.second = v;
		return oldValue;
	}
	else if (m_elements[pos].used == false)
	{
		m_elements[pos].pair = std::make_pair(c, v);
		m_elements[pos].used = true;
		if (pos == m_firstFree)
		{
			if (!findNextFree())
			{
				m_size++;
			}
		}
		else
		{
			m_size++;
		}
	}
	else
	{
		int nextPos = pos;
		while (m_elements[nextPos].next != -1)
		{
			nextPos = m_elements[nextPos].next;
		}
		if (m_elements[nextPos].used == true && m_elements[nextPos].pair.first == c)
		{
			int oldValue = m_elements[nextPos].pair.second;
			m_elements[nextPos].pair.second = v;
			return oldValue;
		}
		m_elements[m_firstFree].pair = std::make_pair(c, v);
		m_elements[m_firstFree].next = -1;
		m_elements[m_firstFree].used = true;
		m_elements[nextPos].next = m_firstFree;	
		if (!findNextFree())
		{
			m_size++;
		}
	}
	return -1;
}

TValue Map::search(TKey c) const
{
	int pos = hash(c, m_capacity);
	while (m_elements[pos].pair.first != c && pos != -1)
	{
		pos = m_elements[pos].next;
	}
	if (!m_elements[pos].used || pos == -1)
	{
		return -1;
	}
	return m_elements[pos].pair.second;
}

TValue Map::remove(TKey c)
{
	if (search(c) == -1)
	{
		return -1;
	}
	else
	{
		int pos = hash(c, m_capacity);
		int prev = -1;
		while (m_elements[pos].pair.first != c && pos != -1)
		{
			prev = pos;
			pos = m_elements[pos].next;
		}
		m_elements[prev].next = m_elements[pos].next;
		int val = m_elements[pos].pair.second;
		m_elements[pos].pair = std::make_pair(DEFAULT_VALUE, DEFAULT_VALUE);
		m_elements[pos].used = false;
		if (m_firstFree > pos)
		{
			m_firstFree = pos;
		}
		m_size--;
		return val;
	}
}

int Map::size() const
{
	return m_size;
}

bool Map::isEmpty() const
{
	return m_size == 0;
}

MapIterator Map::iterator() const
{
	return MapIterator(*this);
}

int Map::addIfNotPresent(Map& m)
{
	int num = 0;
	for (int i = 0; i < m.m_capacity; i++)
	{
		if (m.m_elements[i].used)
		{
			bool found = true;
			int pos = hash(m.m_elements[i].pair.first, m_capacity);
			int prev = pos;
			while (m_elements[pos].pair.first != m.m_elements[i].pair.first && pos != -1)
			{
				prev = pos;
				pos = m_elements[pos].next;
			}
			if (!m_elements[prev].used && pos == -1)
			{
				num++;
				m_elements[prev].pair = m.m_elements[i].pair;
				m_elements[prev].used = true;
				if (prev == m_firstFree)
				{
					if (!findNextFree())
					{
						m_size++;
					}
				}
				else
				{
					m_size++;
				}
			}
			else if(pos == -1)
			{
				m_elements[m_firstFree].pair = m.m_elements[i].pair;
				m_elements[m_firstFree].next = -1;
				m_elements[m_firstFree].used = true;
				m_elements[prev].next = m_firstFree;
				if (!findNextFree())
				{
					m_size++;
				}
			}
		}
	}
	return num;
}

void Map::print() const
{
	for (int i = 0; i < m_capacity; i++)
	{
		std::cout << m_elements[i].pair.first << " " << m_elements[i].pair.second << '\n';
	}
	std::cout << '\n';
}

bool Map::prime(int n) 
{
	for (int i = 2; i <= sqrt(n) + 1; i++)
	{
		if (n % i == 0)
		{
			return false;
		}
	}
	return true;
}

int Map::nextPrime(int n) 
{
	n *= 2;
	while (!prime(n))
	{
		n++;
	}
	return n;
}

bool Map::findNextFree()
{
	while (m_elements[m_firstFree].used && m_firstFree < m_capacity)
	{
		m_firstFree++;
	}
	if (m_firstFree == m_capacity)
	{
		resize();
		return true;
	}
	return false;
}

void Map::resize()
{
	int oldCapacity = m_capacity;
	int newCapacity = Map::nextPrime(m_capacity);
	Element* oldElements = new Element[m_capacity];
	Element* newElements = new Element[newCapacity];
	for (int i = 0; i < m_capacity; i++)
	{
		oldElements[i] = m_elements[i];
	}
	delete[] m_elements;
	m_elements = newElements;
	for (int i = 0; i < newCapacity; i++)
	{
		m_elements[i].pair = std::make_pair(DEFAULT_VALUE, DEFAULT_VALUE);
		m_elements[i].used = false;
		m_elements[i].next = -1;
	}
	m_capacity = newCapacity;
	m_size = 0;
	for (int i = 0; i < oldCapacity; i++)
	{
		if (oldElements[i].used)
		{
			add(oldElements[i].pair.first, oldElements[i].pair.second);
		}
	}
	delete[] oldElements;
}
