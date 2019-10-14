#include <iostream>
#include "Map.h"
#include "..\ShortTest.h"
#include "..\ExtendedTest.h"

int main()
{
	testAll();
	testAllExtended();
	std::cout << "Tests ran successfully!\n";
	/*Map m1;
	m1.add(1, 1);
	m1.add(15, 15);
	Map m2;
	m2.add(1, 1);
	m2.add(2, 2);
	m2.add(3, 3);
	std::cout << m1.addIfNotPresent(m2) << '\n';
	m1.add(28, 28);
	m1.print();*/
	system("pause");
	return 0;
}