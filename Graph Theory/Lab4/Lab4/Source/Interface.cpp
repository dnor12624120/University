#include "Interface.h"

#include <iostream>

Interface::Interface():
	running(true)
{

}

void Interface::run()
{
	while (running)
	{
		std::string input;
		std::cout << ">";
		std::cin >> input;
		if (input == "exit")
		{
			running = false;
		}
		else if (input == "read")
		{
			std::string filepath;
			std::cout << "Enter filepath\n";
			std::cout << "<";
			std::cin >> filepath;
			g.readFromFile(filepath);
			std::cout << "Data read successfully!\n";
		}
		else if (input == "add")
		{
			int x, y, c;
			std::cout << "Enter edge vertices\n";
			std::cout << ">";
			std::cin >> x >> y;
			std::cout << "Enter edge cost\n";
			std::cin >> c;
			g.addEdge(x, y, c);
			std::cout << "Edge added successfully!\n";
		}
		else if (input == "remove")
		{
			int x, y;
			std::cout << "Enter edge vertices\n";
			std::cout << ">";
			std::cin >> x >> y;
			g.removeEdge(x, y);
			std::cout << "Edge removed successfully!\n";
		}
		else if (input == "kruskal")
		{
			std::cout << "Minimum spanning tree of current graph\n";
			auto k = g.kruskal();
			k.print();
		}
		else
		{
			std::cout << "Invalid command\n";
		}
	}
}