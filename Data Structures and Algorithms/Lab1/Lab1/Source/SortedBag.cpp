#include "SortedBag.h"
#include "SortedBagIterator.h"

#include <iostream>
#include <limits>

const int SortedBag::DEFAULT_CAPACITY = 16000;

/*
	Total Complexity: Theta(1)
*/
static void swap(TComp& a, TComp& b)
{
	TComp tmp = a;
	a = b;
	b = tmp;
}

/*
	Total Complexity: Theta(1)
*/
SortedBag::SortedBag(Relation r):
	m_count(0),
	m_capacity(DEFAULT_CAPACITY),
	m_type(r)
{
	m_elements = new TComp[DEFAULT_CAPACITY];
}

/*
	Total Complexity: Theta(1)
*/
SortedBag::~SortedBag()
{
	delete[] m_elements;
}

/*
	Average Complexity: Theta(n)
	Best Case Complexity: Theta(n)
	Worst Case Complexity: Theta(n)
	Total Complexity: O(n)
*/
void SortedBag::add(TComp e)
{
	if (m_count == m_capacity)
	{
		TComp* tmp = new TComp[m_capacity * 2];
		m_capacity *= 2;
		for (int i = 0; i < m_count; i++)
		{
			tmp[i] = m_elements[i];
		}
		delete[] m_elements;
		m_elements = tmp;
	}
	if (m_count == 0)
	{
		m_elements[m_count++] = e;
	}
	else
	{
		int index = 0;
		for (int i = 0; !m_type(m_elements[i], e) && i < m_count; i++)
		{
			index++;
		}
		for (int i = m_count; i > index; i--)
		{
			m_elements[i] = m_elements[i - 1];
		}
		m_elements[index] = e;
		m_count++;
	}
}

/*
	Average Complexity: Theta(n)
	Best Case Complexity: Theta(n)
	Worst Case Complexity: Theta(n)
	Total Complexity: Theta(n)
*/
bool SortedBag::remove(TComp e)
{
	int index;
	for (index = 0; m_elements[index] != e && index < m_count; index++);
	if (index == m_count)
	{
		return false;
	}
	for (int i = index; i < m_count - 1; i++)
	{
		m_elements[i] = m_elements[i + 1];
	}
	m_count--;
	if (m_count <= m_capacity / 4 && m_capacity > SortedBag::DEFAULT_CAPACITY)
	{
		TComp* tmp = new TComp[m_capacity / 2];
		m_capacity /= 2;
		for (int i = 0; i < m_count; i++)
		{
			tmp[i] = m_elements[i];
		}
		delete[] m_elements;
		m_elements = tmp;
	}
	return true;
}

/*
	Average Complexity: Theta(n)
	Best Case Complexity: Theta(1)
	Worst Case Complexity: Theta(n)
	Total Complexity: O(n)
*/
bool SortedBag::search(TComp e) const
{
	return nrOccurrences(e);
}

/*
	Average Complexity: Theta(n)
	Best Case Complexity: Theta(1)
	Worst Case Complexity: Theta(n)
	Total Complexity: O(n)
*/
int SortedBag::nrOccurrences(TComp e) const
{
	int num = 0;
	bool found = false;
	for (int i = 0; i < m_count; i++)
	{
		if (m_elements[i] == e)
		{
			found = true;
			num++;
		}
		else if (found)
		{
			break;
		}
	}
	return num;
}

/*
	Total Complexity: Theta(1)
*/
int SortedBag::size() const
{
	return m_count;
}

/*
	Total Complexity: Theta(1)
*/
SortedBagIterator SortedBag::iterator() const
{
	return SortedBagIterator(*this);
}

/*
	Total Complexity: Theta(1)
*/
bool SortedBag::isEmpty() const
{
	return m_count == 0;
}

/*
	Average Complexity: Theta(n)
	Best Case Complexity: Theta(n)
	Worst Case Complexity: Theta(n)
	Total Complexity: Theta(n)
*/
int SortedBag::elementsWithMaximumFrequency() const
{
	int current_max = 0;
	int max = 0;
	int current_el;
	int count = 0;
	if (m_count == 0)
	{
		return 0;
	}
	if (m_count == 1)
	{
		return 1;
	}
	current_el = m_elements[0];
	for (int i = 0; i < m_count; i++)
	{
		if (m_elements[i] == current_el)
		{
			current_max++;
		}
		else
		{
			if (current_max > max)
			{
				max = current_max;
			}
			current_max = 1;
			current_el = m_elements[i];
		}
	}
	if (current_max > max)
	{
		max = current_max;
	}
	current_el = m_elements[0];
	current_max = 0;
	for (int i = 0; i < m_count; i++)
	{
		if (m_elements[i] == current_el)
		{
			current_max++;
		}
		else
		{
			if (current_max == max)
			{
				count++;
			}
			current_max = 1;
			current_el = m_elements[i];
		}
	}
	if (current_max == max)
	{
		count++;
	}
	return count;
}
