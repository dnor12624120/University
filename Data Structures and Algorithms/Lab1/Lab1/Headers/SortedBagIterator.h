#pragma once

#include "SortedBag.h"

class SortedBagIterator 
{
	public:
		void first();
		void next();
		bool valid() const;

		TElem getCurrent() const;
	private:
		friend class SortedBag;

		SortedBagIterator(const SortedBag& sortedBag);

		const SortedBag& m_container;

		int m_index;
		bool m_valid;
};


