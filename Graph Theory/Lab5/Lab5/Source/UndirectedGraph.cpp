#include "UndirectedGraph.h"

#include <fstream>
#include <tuple>
#include <map>


void UndirectedGraph::readFromFile(const std::string& filepath)
{
	std::ifstream file(filepath);

	file >> m_size >> m_numOfEdges;

	for (int i = 0; i < m_numOfEdges; i++)
	{
		int x, y, c;
		file >> x >> y >> c;
		if (!m_vertices.count(x))
		{
			m_vertices.insert(x);
		}
		if (!m_vertices.count(y))
		{
			m_vertices.insert(y);
		}
		m_edges[std::make_pair(x, y)] = c;
		m_edges[std::make_pair(y, x)] = c;
	}
}


void UndirectedGraph::addEdge(int start, int end, int cost)
{
	m_edges[std::make_pair(start, end)] = cost;
}

void UndirectedGraph::removeEdge(int start, int end)
{
	m_edges.erase(std::make_pair(start, end));
}

int UndirectedGraph::getCost(int start, int end)
{
	if (!m_edges.count(std::make_pair(start, end)))
	{
		return -1;
	}
	return m_edges[std::make_pair(start, end)];
}

UndirectedGraph UndirectedGraph::kruskal(int& cost)
{
	UndirectedGraph tree;
	std::vector<std::tuple<int, int, int>> edges;
	std::vector<std::pair<int, int>> solution;
	std::map<int, int> component, parent, height;
	for (auto edge = m_edges.begin(); edge != m_edges.end(); edge++)
	{
		edges.emplace_back(std::tuple<int, int, int>(edge->first.first, edge->first.second, edge->second));
	}
	std::sort(edges.begin(), edges.end(), [](std::tuple<int, int, int> t1, std::tuple<int, int, int> t2)
	{ return std::get<2>(t1) < std::get<2>(t2); });

	for (auto it = m_vertices.begin(); it != m_vertices.end(); it++)
	{
		component[*it] = parent[*it] = *it;
		height[*it] = 1;
	}

	for (int i = 0; i < edges.size() && solution.size() < m_size; i++)
	{
		int a = root(component[std::get<0>(edges[i])], parent);
		int b = root(component[std::get<1>(edges[i])], parent);
		if (a != b)
		{
			setUnion(a, b, parent, height);
			tree.addEdge(std::get<0>(edges[i]), std::get<1>(edges[i]), std::get<2>(edges[i]));
			cost += std::get<2>(edges[i]);
		}
	}

	return tree;
}

int UndirectedGraph::root(int vertex, std::map<int, int>& parent)
{
	while (vertex != parent[vertex])
	{
		vertex = parent[vertex];
	}
	return vertex;
}

void UndirectedGraph::setUnion(int vertex1, int vertex2, std::map<int, int>& parent, std::map<int, int>& height)
{
	if (height[vertex1] > height[vertex2])
	{
		parent[vertex2] = vertex1;
	}
	else
	{
		parent[vertex1] = vertex2;
		if (height[vertex1] == height[vertex2])
		{
			height[vertex2]++;
		}
	}
}

void UndirectedGraph::print() const
{
	for (auto it = m_edges.begin(); it != m_edges.end(); it++)
	{
		std::cout << it->first.first << " " << it->first.second << " : " << it->second << '\n';
	}
}

const bool UndirectedGraph::complete()
{
	return m_numOfEdges == (m_size * (m_size - 1)) / 2;
}

const int UndirectedGraph::getTotalCost() const
{
	int totalCost = 0;
	for (auto edge = m_edges.begin(); edge != m_edges.end(); edge++)
	{
		totalCost += edge->second;
	}
	return totalCost / 2;
}