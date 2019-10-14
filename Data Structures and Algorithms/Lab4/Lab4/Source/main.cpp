#include <iostream>
#include <cassert>

#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include "..\ExtendedTest.h"
#include "..\ShortTest.h"


int main()
{
	testAll();
	testAllExtended();
	{
		SortedMultiMap smm([](int a, int b){ return a < b; });
		smm.add(3, 5);
		smm.add(2, 1);
		smm.add(4, 5);
		smm.add(1, 23);
		smm.add(13, 5);
		smm.add(3, 6);
		smm.print();
		auto it = smm.iterator();
		it.first();
		it.next();
		it.next();
		it.next();
		std::cout << it.getCurrent().first << ' ' << it.getCurrent().second << '\n';
		it.jumpBack(2);
		std::cout << it.getCurrent().first << ' ' << it.getCurrent().second << '\n';
		it.jumpBack(1);
		std::cout << it.getCurrent().first << ' ' << it.getCurrent().second << '\n';
	}
	{
		SortedMultiMap smm([](int a, int b){ return a < b; });
		bool e = false;
		try
		{
			auto it = smm.iterator();
			it.jumpBack(6);
		}
		catch (...)
		{
			e = true;
		}
		assert(e == true);
	}
	system("pause");
	return 0;
}