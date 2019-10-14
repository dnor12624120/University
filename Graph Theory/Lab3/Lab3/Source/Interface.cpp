#include "Interface.h"

#include <iostream>
#include <string>

Interface::Interface() :
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
			std::cout << ">";
			std::cin >> filepath;
			g.readFromFile(filepath);
			std::cout << "Data read successfully!\n";
		}
		else if (input == "ae")
		{
			int x, y;
			std::cout << "Enter vertices\n";
			std::cout << ">";
			std::cin >> x >> y;
			g.addEdge(x, y);
			std::cout << "Edge added successfully!\n";
		}
		else if (input == "av")
		{
			int x;
			std::cout << "Enter vertex\n";
			std::cout << ">";
			std::cin >> x;
			g.addVertex(x);
			std::cout << "Vertex added successfully!\n";
		}
		else if(input == "sc")
		{
			int x, y, c;
			std::cout << "Enter vertices\n";
			std::cout << ">";
			std::cin >> x >> y;
			std::cout << "Enter cost\n";
			std::cout << ">";
			std::cin >> c;
			g.setEdgeData(x, y, c);
			std::cout << "Cost set successfully!\n";
		}
		else if (input == "re")
		{
			int x, y;
			std::cout << "Enter vertices\n";
			std::cout << ">";
			std::cin >> x >> y;
			g.removeEdge(x, y);
			std::cout << "Edge removed successfully!\n";
		}
		else if (input == "rv")
		{
			int x;
			std::cout << "Enter vertex\n";
			std::cout << ">";
			std::cin >> x;
			g.removeVertex(x);
			std::cout << "Vertex removed successfully!\n";
		}
		else if (input == "dijkstra")
		{
			int x, y;
			std::cout << "Enter start index!\n";
			std::cout << ">";
			std::cin >> x;
			std::cout << "Enter end index!\n";
			std::cout << ">";
			std::cin >> y;
			auto l = g.dijkstra(x, y);
			int start = x;
			int end = y;
			std::cout << "Shortest cost path:\n";
			while (start != end)
			{
				std::cout << start << " -> " << l[start] << ' ' << ' ' << g.getEdgeData(start, l[start]) << '\n';
				start = l[start];
			}
		}
		else
		{
			std::cout << "Invalid input\n";
		}
	}
}