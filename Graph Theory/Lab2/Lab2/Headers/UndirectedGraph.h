#pragma once

#include <string>
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>

class UndirectedGraph
{
	public:
		UndirectedGraph() = default;

		void readFromFile(const std::string& filepath);
		std::vector<UndirectedGraph> getConnectedComponents();

		void addVertex(int vertex);
		void removeVertex(int vertex);
		void addEdge(int start, int end);
		void removeEdge(int start, int end);
		const std::vector<int>& adjacentVertices(int vertex);

		void print();

	private:
		void depthFirstSearch(int index, std::map<int, bool>& visited, UndirectedGraph& currentComponent);
		std::map<int, std::vector<int>> m_adjacencyList;
};

