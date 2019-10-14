#include "Interface.h"

#include <string>
#include <iostream>

Interface::Interface():
	m_running(true)
{

}

void Interface::run()
{
	while (m_running)
	{
		std::string command;
		std::cout << ">";
		std::getline(std::cin, command);
		if (command == "read")
		{
			readFromFile();
		}
		else if (command == "addv")
		{
			addVertex();
		}
		else if (command == "rmv")
		{
			removeVertex();
		}
		else if (command == "adde")
		{
			addEdge();
		}
		else if (command == "rme")
		{
			removeEdge();
		}
		else if (command == "cc")
		{
			getConnectedComponents();
		}
		else if (command == "print")
		{
			print();
		}
	}
}

void Interface::readFromFile()
{
	std::string filepath;
	std::cout << "Enter filepath: ";
	std::getline(std::cin, filepath);
	graph.readFromFile(filepath);
	std::cout << "Graph read successfully!\n";
}

void Interface::addVertex()
{
	int x;
	std::cout << "Enter vertex index: ";
	std::cin >> x;
	graph.addVertex(x);
}

void Interface::removeVertex()
{
	int x;
	std::cout << "Enter vertex index: ";
	std::cin >> x;
	graph.removeVertex(x);
}

void Interface::addEdge()
{
	int x, y;
	std::cout << "Enter edge vertices: ";
	std::cin >> x >> y;
	graph.addEdge(x, y);
}

void Interface::removeEdge()
{
	int x, y;
	std::cout << "Enter edge vertices: ";
	std::cin >> x >> y;
	graph.removeEdge(x, y);
}

void Interface::getConnectedComponents()
{
	std::cout << "Connected components:\n";
	for (auto c : graph.getConnectedComponents())
	{
		c.print();
		std::cout << "=================" << '\n';
	}
}

void Interface::print()
{
	graph.print();
}