#pragma once

#include <utility>

class Map;

typedef std::pair<int, int> TElem;

class MapIterator
{
	public:
		/*
			Average Complexity: Theta(m)
			Best Case: Theta(1)
			Worst Case: Theta(m)
			Total Complexity: O(m)
		*/
		void first();

		/*
			Average Complexity: Theta(m)
			Best Case: Theta(1)
			Worst Case: Theta(m)
			Total Complexity: O(m)
		*/
		void next();

		/*
			Total Complexity: Theta(1)
		*/
		bool valid() const;

		/*
			Total Complexity: Theta(1)
		*/
		TElem getCurrent() const;
	private:
		friend class Map;

		/*
			Average Complexity : Theta(m)
			Best Case : Theta(1)
			Worst Case : Theta(m)
			Total Complexity : O(m)
		*/
		MapIterator(const Map& map);

		const Map& m_map;
		int m_current;
};