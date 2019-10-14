#include "SortedMultiMap.h"
#include "SMMIterator.h"

#include <iostream>

SortedMultiMap::SortedMultiMap(Relation r):
	m_elements(nullptr),
	m_capacity(DEFAULT_CAPACITY),
	m_size(0),
	m_root(-1),
	m_firstFree(0),
	m_relation(r)
{
	m_elements = new Node[m_capacity];
	m_nextFree = new int[m_capacity];
	for (int i = 0; i < m_capacity; i++)
	{
		m_elements[i].left = -1;
		m_elements[i].right = -1;
		m_elements[i].parent = -1;
		m_nextFree[i] = i + 1;
	}
	m_nextFree[m_capacity - 1] = -1;
}

SortedMultiMap::~SortedMultiMap()
{
	delete[] m_elements;
	delete[] m_nextFree;
}

void SortedMultiMap::add(TKey c, TValue v)
{
	if (m_size == m_capacity)
	{
		resize();
	}
	//we're inserting at the root position
	if (m_root == -1)
	{
		m_elements[m_firstFree].pair = std::make_pair(c, v);
		m_elements[m_firstFree].left = -1;
		m_elements[m_firstFree].right = -1;
		m_elements[m_firstFree].parent = -1;
		m_root = m_firstFree;
		m_firstFree = m_nextFree[m_firstFree];
	}
	else
	{
		m_elements[m_firstFree].pair = std::make_pair(c, v);
		bool found = false;
		int current = m_root;
		while (!found)
		{	
			if (m_relation(m_elements[current].pair.first, c) || m_elements[current].pair.first == c)
			{
				//right child is empty - we can insert
				if (m_elements[current].right == -1)
				{
					m_elements[current].right = m_firstFree;
					m_elements[m_firstFree].parent = current;
					m_elements[m_firstFree].left = -1;
					m_elements[m_firstFree].right = -1;
					found = true;
					m_firstFree = m_nextFree[m_firstFree];
				}
				//right child is not empty, we'll look at the children of this node
				else
				{
					current = m_elements[current].right;
				}
			}
			else
			{
				//left child is empty - we can insert
				if (m_elements[current].left == -1)
				{
					m_elements[current].left = m_firstFree;
					m_elements[m_firstFree].left = -1;
					m_elements[m_firstFree].right = -1;
					m_elements[m_firstFree].parent = current;
					found = true;
					m_firstFree = m_nextFree[m_firstFree];
				}
				//left child is not empty, we'll look at the children of this node
				else
				{
					current = m_elements[current].left;
				}
			}
		}
	}
	m_size++;
}

vector<TValue> SortedMultiMap::search(TKey c) const
{
	vector<TValue> values;
	int current = m_root;
	while (current != -1)
	{
		if (m_elements[current].pair.first == c)
		{
			values.emplace_back(m_elements[current].pair.second);
		}
		if (m_relation(m_elements[current].pair.first, c))
		{
			current = m_elements[current].right;
		}
		else
		{
			current = m_elements[current].left;
		}
	}
	return values;
}

bool SortedMultiMap::remove(TKey c, TValue v)
{
	int current = m_root;
	while (m_elements[current].pair != std::make_pair(c, v) && current != -1)
	{
		if (m_relation(m_elements[current].pair.first, c))
		{
			current = m_elements[current].right;
		}
		else
		{
			current = m_elements[current].left;
		}
	}
	if (current == -1)
	{
		return false;
	}
	else
	{
		//element has no children, we can simply remove it
		if (m_elements[current].left == -1 && m_elements[current].right == -1)
		{
			int parent = m_elements[current].parent;
			if (parent != -1)
			{
				int parentsLeft = m_elements[parent].left;
				int parentsRight = m_elements[parent].right;
				if (m_elements[parentsLeft].pair == m_elements[current].pair)
				{
					m_elements[parent].left = -1;
				}
				else
				{
					m_elements[parent].right = -1;
				}
			}
			m_elements[current].parent = -1;
			findNextFree(current);
			if (current == m_root)
			{
				m_root = -1;
			}
		}
		else if (m_elements[current].left != -1 && m_elements[current].right == -1)
		{
			int parent = m_elements[current].parent;
			int leftChild = m_elements[current].left;
			if (m_elements[current].parent != -1)
			{
				int parentsLeft = m_elements[parent].left;
				int parentsRight = m_elements[parent].right;
				if (m_elements[parentsLeft].pair == m_elements[current].pair)
				{
					m_elements[parent].left = leftChild;
				}
				else
				{
					m_elements[parent].right = leftChild;
				}
			}
			if (current == m_root)
			{
				m_root = leftChild;
			}
			m_elements[leftChild].parent = parent;
			m_elements[current].left = -1;
			m_elements[current].parent = -1;
			findNextFree(current);
		}
		else if (m_elements[current].left == -1 && m_elements[current].right != -1)
		{
			int parent = m_elements[current].parent;
			int rightChild = m_elements[current].right;
			int parentsLeft = m_elements[parent].left;
			int parentsRight = m_elements[parent].right;
			if (m_elements[current].parent != -1)
			{
				if (m_elements[parentsLeft].pair == m_elements[current].pair)
				{
					m_elements[parent].left = rightChild;
				}
				else
				{
					m_elements[parent].right = rightChild;
				}
			}
			if (current == m_root)
			{
				m_root = rightChild;
			}
			m_elements[rightChild].parent = parent;
			m_elements[current].right = -1;
			m_elements[current].parent = -1;
			findNextFree(current);
		}
		else
		{
			int parent = m_elements[current].parent;
			int currentLeft = m_elements[current].left;
			int currentRight = m_elements[current].right;
			int rightmostChild = m_elements[current].left;
			while (m_elements[rightmostChild].right != -1)
			{
				rightmostChild = m_elements[rightmostChild].right;
			}
			int rightmostLeft = m_elements[rightmostChild].left;
			int rightmostParent = m_elements[rightmostChild].parent;
			//parents child points to replacement
			if (parent != -1)
			{
				if (m_elements[m_elements[parent].left].pair == m_elements[current].pair)
				{
					m_elements[parent].left = rightmostChild;
				}
				else
				{
					m_elements[parent].right = rightmostChild;
				}
			}
			//replacements parent points to the initial parent
			m_elements[rightmostChild].parent = parent;
			if (m_elements[current].right != -1)
			{
				m_elements[rightmostChild].right = m_elements[current].right;
				m_elements[m_elements[current].right].parent = rightmostChild;
			}
			if (m_elements[current].left != -1)
			{
				if (m_elements[current].left != rightmostChild)
				{
					m_elements[rightmostChild].left = m_elements[current].left;
					m_elements[m_elements[current].left].parent = rightmostChild;
				}
			}
			if (rightmostLeft != -1 && m_elements[current].left != rightmostChild)
			{
				m_elements[rightmostParent].right = rightmostLeft;
				m_elements[rightmostLeft].parent = rightmostParent;
			}
			if (current == m_root)
			{
				m_root = rightmostChild;
			}
			m_elements[current].left = -1;
			m_elements[current].right = -1;
			m_elements[current].parent = -1;
			findNextFree(current);
		}
		m_size--;
		return true;
	}
}

int SortedMultiMap::size() const
{
	return m_size;
}

bool SortedMultiMap::isEmpty() const
{
	return m_size == 0;
}

SMMIterator SortedMultiMap::iterator() const
{
	return SMMIterator(*this);
}

/*
	Total Complexity: Theta(n)
	Best Case: Theta(n)
	Worst Case: Theta(n)
	Average Complexity: Theta(n)
*/
vector<TValue> SortedMultiMap::valueBag() const
{
	vector<TValue> values;
	stack<TValue> stack;
	stack.push(m_root);

	while (!stack.empty())
	{
		TValue index = stack.top();
		stack.pop();
		if (index != -1)
		{
			values.emplace_back(m_elements[index].pair.second);
			if (m_elements[index].left != -1)
			{
				stack.push(m_elements[index].left);
			}
			if (m_elements[index].right != -1)
			{
				stack.push(m_elements[index].right);
			}
		}
	}

	return values;
}

void SortedMultiMap::resize()
{
	Node* newElements = new Node[m_capacity * 2];
	int* newNextFree = new int[m_capacity * 2];
	for (int i = 0; i < m_capacity; i++)
	{
		newElements[i] = m_elements[i];
		m_nextFree[i] = m_nextFree[i];
	}
	for (int i = m_capacity; i < 2 * m_capacity - 1; i++)
	{
		newElements[i].left = -1;
		newElements[i].right = -1;
		newElements[i].parent = -1;
		newNextFree[i] = i + 1;
	}
	m_firstFree = m_capacity;
	newNextFree[2 * m_capacity - 1] = -1;
	delete[] m_elements;
	delete[] m_nextFree;
	m_elements = newElements;
	m_nextFree = newNextFree;
	m_capacity *= 2;
}

void SortedMultiMap::findNextFree(int current)
{
	if (m_firstFree > current)
	{
		int oldFirstFree = m_firstFree;
		m_firstFree = current;
		m_nextFree[m_firstFree] = oldFirstFree;
	}
	else
	{
		int oldNextFree = m_nextFree[m_firstFree];
		m_nextFree[m_firstFree] = current;
		m_nextFree[current] = oldNextFree;
	}
}

void SortedMultiMap::print() const
{
	for (int i = 0; i < m_capacity; i++)
	{
		std::cout << "Key: " << m_elements[i].pair.first << '\n';
		std::cout << "Value: " << m_elements[i].pair.second << '\n';
		std::cout << "Left: " << m_elements[i].left << '\n';
		std::cout << "Right: " << m_elements[i].right << '\n';
		std::cout << "Parent: " << m_elements[i].parent << '\n';
		std::cout << "Next free: " << m_nextFree[i] << '\n' << '\n';
	}
}
