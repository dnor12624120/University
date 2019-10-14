#pragma once

#include <utility>

typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;

class DLLA;

class DLLAIterator
{
	public:
		void first();
		void next();
		bool valid() const;
		TElem getCurrent() const;
	private:
		friend class DLLA;

		DLLAIterator(const DLLA& c);
		const DLLA& m_container;
		int m_index;
};


