#pragma once

#define DEFAULT_CAPACITY 64

#include <utility>

class Heap
{
	typedef bool(*Relation)(int, int);

	public:
		Heap() = default;
		Heap(Relation relation);
		~Heap();

		void push(const std::pair<int, int>& value);
		const std::pair<int, int>& top() const;
		void pop();
		int search(int value);
		
		/*
			Total Complexity: Theta(1)
		*/
		inline const int size() const
		{
			return m_size;
		}
	private:
		/*
			Total Complexity: Theta(1)
		*/
		inline const bool validIndex(int index) const
		{
			return index < m_size;
		}
		void resize();

		std::pair<int, int>* m_elements;
		int m_size;
		int m_capacity;

		Relation m_relation;
};