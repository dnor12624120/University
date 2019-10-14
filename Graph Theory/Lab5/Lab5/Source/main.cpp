#include "UndirectedGraph.h"
#include <iostream>

int main()
{
	UndirectedGraph g;
	g.readFromFile("graph.txt");
	if (g.complete())
	{
		std::cout << "Graph total cost: " << g.getTotalCost() << '\n';
		int cost = 0;
		auto h = g.kruskal(cost);
		std::cout << "Minimum spanning tree cost: " << cost << '\n';
		std::cout << "Minimum spanning tree:\n";
		h.print();
	}
	else
	{
		std::cout << "Graph doesn't satisfy the triangle inequality\n";
	}
	system("pause");
	return 0;
}