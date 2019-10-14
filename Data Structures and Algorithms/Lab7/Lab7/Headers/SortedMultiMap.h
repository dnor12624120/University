#pragma once

#include <vector>
#include <utility>

#define DEFAULT_CAPACITY 16

typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
typedef bool(*Relation)(TKey, TKey);

struct Node
{
	TElem pair;
	int left;
	int right;
	int parent;	
};

class SMMIterator;

using namespace std;

class SortedMultiMap
{
	public:
		/*
			Total Complexity: Theta(n)
		*/
		SortedMultiMap(Relation r);

		/*
			Total Complexity: Theta(1)
		*/
		~SortedMultiMap();

		/*
			Total Complexity: Theta(n)
			Best Case: Theta(1)
			Worst Case: Theta(n)
			Average Complexity: O(n)
		*/
		void add(TKey c, TValue v);

		/*
			Total Complexity: Theta(n)
			Best Case: Theta(1)
			Worst Case: Theta(n)
			Average Complexity: O(n)
		*/
		vector<TValue> search(TKey c) const;

		/*
			Total Complexity: Theta(n)
			Best Case: Theta(1)
			Worst Case: Theta(n)
			Average Complexity: O(n)
		*/
		bool remove(TKey c, TValue v);

		/*
			Total Complexity: Theta(1)
		*/
		int size() const;

		/*
			Total Complexity: Theta(1)
		*/
		bool isEmpty() const;

		/*
			Total Complexity: Theta(1)
		*/
		SMMIterator iterator() const;
	
		/*
			Total Complexity: Theta(n)
		*/
		void print() const;

		/*
			Total Complexity: Theta(1)
		*/
		inline const int getRoot() const { return m_root; }

		/*
			Total Complexity: Theta(n)
		*/
		vector<TValue> valueBag() const;
	private:
		friend class SMMIterator;

		/*
			Total Complexity: Theta(newSize)
		*/
		void resize();
		/*
			Total Complexity: Theta(1)
		*/
		void findNextFree(int current);

		Node* m_elements;
		int* m_nextFree;
		int m_capacity;
		int m_size;
		int m_root;
		int m_firstFree;
		Relation m_relation;
};
