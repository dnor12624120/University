#include <iostream>
#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include "ShortTest.h"
#include "ExtendedTest.h"

int main()
{
	testAll();
	std::cout << "Short test ran successfully!\n";
	testAllExtended();
	std::cout << "Extended test ran successfully!\n";
	/*SortedMultiMap m([](int a, int b) { return a <= b; });
	m.add(4, 3);
	m.add(3, 345);
	m.add(123, 234);
	m.add(33, 2);
	m.add(32, 3);
	m.add(41, 2);
	m.add(56, 3);
	m.add(1, 1);

	auto v = m.valueBag();
	for (auto x : v)
	{
		std::cout << x << '\n';
	}*/

	system("pause");
	return 0;
}