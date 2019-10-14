#include "DLLA.h"
#include "DLLAIterator.h"

#include <iostream>

/*
	Total Complexity: Theta(n)
*/
DLLA::DLLA() :
	m_size(0),
	m_capacity(DEFAULT_CAPACITY),
	m_head(-1),
	m_tail(-1),
	m_firstFree(0)
{
	m_elements = new Node[m_capacity];
	for (int i = 0; i < m_capacity; i++)
	{
		m_elements[i].next = i + 1;
		m_elements[i].prev = i - 1;
	}
	m_elements[m_capacity - 1].next = -1;
}

/*
	Total Complexity: Theta(1)
*/
DLLA::~DLLA()
{
	delete[] m_elements;
}

/*
	Average Complexity: Theta(n)
	Best Case: Theta(1)
	Worst Case: Theta(n)
	Total Complexity: O(n)
*/
void DLLA::insert(TElem pair, int position)
{
	if (position < 0 || position > m_size)
	{
		throw std::exception("Position out of range!");
	}
	if (m_size == m_capacity)
	{
		resize();
		for (int i = m_capacity / 2; i < m_capacity; i++)
		{
			m_elements[i].next = i + 1;
			m_elements[i].prev = i - 1;
		}
		m_elements[m_capacity - 1].next = -1;
		m_firstFree = m_capacity / 2;
	}
	if (position == 0)
	{
		if (m_head == -1)
		{
			m_firstFree = m_elements[m_firstFree].next;
			m_head = position;
			m_tail = position;
			m_elements[position].pair = pair;
			m_elements[position].prev = -1;
			m_elements[position].next = -1;
		}
		else
		{
			int newPosition = m_firstFree;
			m_firstFree = m_elements[m_firstFree].next;
			m_elements[newPosition].pair = pair;
			m_elements[newPosition].prev = -1;
			m_elements[newPosition].next = m_head;
			m_elements[m_head].prev = newPosition;
			m_head = newPosition;
		}
	}
	else
	{
		int newPosition = m_firstFree;
		int index = m_head;
		int counter = 0;
		m_firstFree = m_elements[m_firstFree].next;
		m_elements[newPosition].pair = pair;
		while (index != -1 && counter < position - 1)
		{
			index = m_elements[index].next;
			counter++;
		}
		m_elements[newPosition].next = m_elements[index].next;
		m_elements[index].next = newPosition;
		m_elements[newPosition].prev = index;
		if (m_elements[newPosition].next == -1)
		{
			m_tail = newPosition;
			m_elements[newPosition].next = -1;
		}
		else
		{
			m_elements[m_elements[index].next].prev = newPosition;
		}

	}
	m_size++;
}

/*
	Average Complexity: Theta(n)
	Best Case: Theta(1)
	Worst Case: Theta(n)
	Total Complexity: O(n)
*/
void DLLA::remove(int position)
{
	if (position < 0 || position > m_size)
	{
		throw std::exception("Position out of range!");
	}
	if (position == 0)
	{
		if (m_head == m_tail)
		{
			m_elements[m_head].next = m_firstFree;
			m_elements[m_firstFree].prev = m_head;
			m_firstFree = m_head;
			m_head = -1;
			m_tail = -1;
		}
		else
		{
			int newHead = m_elements[m_head].next;
			m_elements[m_head].next = m_firstFree;
			m_elements[m_firstFree].prev = m_head;
			m_firstFree = m_head;
			m_head = newHead;
			m_elements[m_head].prev = -1;
		}
	}
	else if (position == m_size - 1)
	{
		int newTail = m_elements[m_tail].prev;
		m_elements[m_tail].next = m_firstFree;
		m_elements[m_firstFree].prev = m_tail;
		m_firstFree = m_tail;
		m_tail = newTail;
		m_elements[m_tail].next = -1;
	}
	else
	{
		int index = m_head;
		int counter = 0;
		while (index != -1 && counter < position - 1)
		{
			index = m_elements[index].next;
			counter++;
		}
		int removedIndexNext = m_elements[m_elements[index].next].next;
		m_elements[m_elements[index].next].next = m_firstFree;
		m_elements[m_firstFree].prev = m_elements[index].next;
		m_firstFree = m_elements[index].next;
		m_elements[index].next = removedIndexNext;
		m_elements[removedIndexNext].prev = index;
	}
	m_size--;
}

/*
	Average Complexity: Theta(n)
	Best Case: Theta(1)
	Worst Case: Theta(n)
	Total Complexity: O(n)
*/
int DLLA::search(TElem pair) const
{
	for (int i = m_head, counter = 0; i != -1; i = m_elements[i].next, counter++)
	{
		if (m_elements[i].pair == pair)
		{
			return counter;
		}
	}
	return -1;
}

/*
	Total Complexity: Theta(n)
*/
void DLLA::resize() 
{
	Node* tempArray = new Node[m_capacity * 2];
	for (int i = 0; i < m_size; i++)
	{
		tempArray[i] = m_elements[i];
	}
	delete[] m_elements;
	m_elements = tempArray;
	m_capacity *= 2;
}

/*
	Total Complexity: Theta(1)
*/
DLLAIterator DLLA::iterator() const
{
	return DLLAIterator(*this);
}

/*
	Average Complexity: Theta(n)
	Best Case: Theta(1)
	Worst Case: Theta(n)
	Total Complexity: O(n)
*/
Node DLLA::operator[](int position) const
{
	int counter = 0;
	int index = m_head;
	while (index != -1 && counter < position)
	{
		counter++;
		index = m_elements[index].next;
	}
	return m_elements[index];
}

/*
	Total Complexity: Theta(n)
*/
void DLLA::print() const
{
	for (int i = m_head; i != -1; i = m_elements[i].next)
	{
		std::cout << "Pair: " << m_elements[i].pair.first << " : " << m_elements[i].pair.second << '\n';
		std::cout << "Next: " << m_elements[i].next << '\n';
		std::cout << "Prev: " << m_elements[i].prev << '\n' << '\n';
	}
}