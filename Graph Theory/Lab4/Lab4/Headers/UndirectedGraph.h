#pragma once

#include <string>
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <map>


class UndirectedGraph
{
	public:
		UndirectedGraph() = default;

		void readFromFile(const std::string& filepath);

		void addEdge(int start, int end, int cost);
		void removeEdge(int start, int end);

		UndirectedGraph kruskal();

		void print() const;

	private:
		int root(int vertex, std::map<int, int>& parent);
		void setUnion(int vertex1, int vertex2, std::map<int, int>& parent, std::map<int, int>& height);

		std::set<int> m_vertices;
		std::map<std::pair<int, int>, int> m_edges;
		int m_size;
};
