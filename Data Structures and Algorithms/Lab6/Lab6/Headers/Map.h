#pragma once

#define NULL_TVALUE -1

#include <utility>

typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;

class MapIterator;

struct Element
{
	TElem pair;
	int next;
	bool used;

	/*
		Total Complexity: Theta(1)
	*/
	Element() = default;

	/*
		Total Complexity: Theta(1)
	*/
	Element(TElem p, int n, bool u) :
		pair(p), next(n), used(u)
	{

	}
};

class Map 
{
	public:
		/*
			Total Complexity: Theta(1)
		*/
		Map();

		/*
			Total Complexity: Theta(1)
		*/
		~Map();

		/*
			Average Complexity: Theta(1)
			Best Case: Theta(1)
			Worst Case: Theta(n)
			Total Complexity: O(n)
		*/
		TValue add(TKey c, TValue v);

		/*
			Average Complexity: Theta(n)
			Best Case: Theta(1)
			Worst Case: Theta(n)
			Total Complexity: O(n)
		*/
		TValue search(TKey c) const;

		/*
			Average Complexity: Theta(n)
			Best Case: Theta(1)
			Worst Case: Theta(n)
			Total Complexity: O(n)
		*/
		TValue remove(TKey c);

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
		MapIterator iterator() const;

		/*
			Total Complexity: Theta(m)
		*/
		void print() const;

		/*
			Average Complexity: Theta(m + n)
			Best Case: Theta(m)
			Worst Case: Theta(m + n)
			Total Complexity: O(m + n)
		*/
		int addIfNotPresent(Map& m);
	private:
		/*
			Average Complexity: Theta(sqrt(n))
			Best Case: Theta(1)
			Worst Case: Theta(sqrt(n))
			Total Complexity: O(sqrt(n))
		*/
		static bool prime(int n);

		/*
			Total Complexity: whatever the frequency of prime numbers is 
		*/
		static int nextPrime(int n);

		/*
			Average Complexity: Theta(m)
			Best Case: Theta(1)
			Worst Case: Theta(m)
			Total Complexity: O(m)
		*/
		bool findNextFree();

		/*
			Total Complexity: Theta(new_m);
		*/
		void resize();
		
		/*
			Total Complexity: Theta(1)
		*/
		inline const int hash(int key, int size) const
		{
			return abs(key % size);
		}

		friend class MapIterator;

		int m_size;
		int m_capacity;
		Element* m_elements;
		int m_firstFree;
};