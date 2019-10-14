#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include "DLLAIterator.h"

/*
	Total Complexity: Theta(1)
*/
SortedMultiMap::SortedMultiMap(Relation r):
	m_relation(r)
{

}

/*
	Total Complexity: Theta(1)
*/
SortedMultiMap::~SortedMultiMap()
{

}

/*
	Average Complexity: Theta(n^2)
	Best Case: Theta(1)
	Worst Case: Theta(n^2)
	Total Complexity: O(n^2)
*/
void SortedMultiMap::add(TKey c, TValue v)
{
	if (m_elements.size() == 0)
	{
		m_elements.insert(std::make_pair(c, v), 0);
	}
	else
	{
		auto it = m_elements.iterator();
		int counter = 0;
		it.first();
		while (it.valid() && m_relation(it.getCurrent().first, c))
		{
			it.next();
			counter++;
		}
		m_elements.insert(std::make_pair(c, v), counter);
	}
}

/*
	Average Complexity: Theta(n)
	Best Case: Theta(1)
	Worst Case: Theta(n)
	Total Complexity: O(n)
*/
vector<TValue> SortedMultiMap::search(TKey c) const
{
	vector<TValue> values;
	auto it = m_elements.iterator();
	while (it.valid() && it.getCurrent().first != c)
	{
		it.next();
	}
	while (it.valid() && it.getCurrent().first == c)
	{
		values.emplace_back(it.getCurrent().second);
		it.next();
	}
	return values;
}

/*
	Average Complexity: Theta(n^2)
	Best Case: Theta(1)
	Worst Case: Theta(n^2)
	Total Complexity: O(n^2)
*/
bool SortedMultiMap::remove(TKey c, TValue v)
{
	int index = m_elements.search(std::make_pair(c, v));
	if (index == -1)
	{
		return false;
	}
	else
	{
		m_elements.remove(index);
		return true;
	}
}

/*
	Total Complexity: Theta(1)
*/
int SortedMultiMap::size() const
{
	return m_elements.size();
}

/*
	Total Complexity: Theta(1)
*/
bool SortedMultiMap::isEmpty() const
{
	return m_elements.size() == 0;
}

/*
	Total Complexity: Theta(1)
*/
SMMIterator SortedMultiMap::iterator()
{
	return SMMIterator(*this);
}

/*
	Total Complexity: Theta(n)
*/
void SortedMultiMap::print() const
{
	m_elements.print();
}