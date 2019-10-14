#pragma once

class SortedBagIterator;

typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);

class SortedBag 
{
	public:
		SortedBag(Relation r);
		~SortedBag();

		void add(TComp e);
		bool remove(TComp e);
		bool search(TComp e) const;
		int nrOccurrences(TComp e) const;
		int size() const;
		SortedBagIterator iterator() const;
		bool isEmpty() const;		
		int elementsWithMaximumFrequency() const;
	private:
		friend class SortedBagIterator;

		unsigned int m_count;
		unsigned int m_capacity;
		TComp* m_elements;

		Relation m_type;

		const static int DEFAULT_CAPACITY;
};