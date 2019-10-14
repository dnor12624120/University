#pragma once

#define DEFAULT_CAPACITY 64

#include <utility>
#include <exception>

typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
typedef bool(*Relation)(TKey, TKey);

class DLLAIterator;

struct Node
{
	TElem pair;
	int next;
	int prev;
};

class DLLA
{
	public:
		DLLA();
		~DLLA();

		void insert(TElem pair, int position);
		void remove(int positiion);
		int search(TElem pair) const;
		DLLAIterator iterator() const;
		void print() const;
		Node operator[](int index) const;
		inline const int size() const
		{
			return m_size;
		}
		inline const int head() const
		{
			return m_head;
		}
	private:
		friend class DLLAIterator;	

		void resize();

		Node* m_elements;
		int m_size;
		int m_capacity;

		int m_head;
		int m_tail;
		int m_firstFree;
};
