#include "UndirectedGraph.h"

#include <stack>
#include <exception>
#include <fstream>

/*
	Reads vertex and edge data for a graph from a file.
	Preconditions:
		filepath must be a valid filepath.
	Parameters:
		filepath - filepath that data will be read from.
	Throws:
		std::exception - if filepath is not valid.
*/
void UndirectedGraph::readFromFile(const std::string& filepath)
{
	std::ifstream inputFile(filepath);
	int numOfVertices;
	int numOfEdges;

	if (inputFile.bad())
	{
		throw std::exception("Invalid input file!");
	}

	inputFile >> numOfVertices;
	inputFile >> numOfEdges;

	for (int i = 0; i < numOfVertices; i++)
	{
		m_adjacencyList[i] = std::vector<int>();
	}

	for (int i = 0; i < numOfEdges; i++)
	{
		int x, y;
		inputFile >> x >> y;
		m_adjacencyList[x].emplace_back(y);
		m_adjacencyList[y].emplace_back(x);
	}

	inputFile.close();
}

/*
	Returns an array of arrays containing the connected components of the graph.
*/
std::vector<UndirectedGraph> UndirectedGraph::getConnectedComponents()
{
	std::vector<UndirectedGraph> components;
	std::map<int, bool> visited;
	std::for_each(m_adjacencyList.begin(), m_adjacencyList.end(), [&visited](auto x){ visited[x.first] = false; });

	for (auto i = visited.begin(); i != visited.end(); i++)
	{
		if (!i->second)
		{
			UndirectedGraph currentComponent;
			depthFirstSearch(i->first, visited, currentComponent);
			components.emplace_back(currentComponent);
		}
	}

	return components;
}

void UndirectedGraph::depthFirstSearch(int index, std::map<int, bool>& visited, UndirectedGraph& currentComponent)
{
	std::stack<int> s;
	s.push(index);
	while (!s.empty())
	{
		int vertex = s.top();
		s.pop();
		currentComponent.addVertex(vertex);
		if (!visited[vertex])
		{
			visited[vertex] = true;
		}
		for (auto i = m_adjacencyList[vertex].begin(); i != m_adjacencyList[vertex].end(); i++)
		{
			if (!visited[*i])
			{
				s.push(*i);
				currentComponent.addVertex(*i);
				for (auto j : adjacentVertices(*i))
				{
					currentComponent.addEdge(*i, j);
				}
				visited[*i] = true;
			}
		}
	}
}

void UndirectedGraph::addVertex(int vertex)
{
	if (!m_adjacencyList.count(vertex))
	{
		m_adjacencyList[vertex] = std::vector<int>();
	}
}

void UndirectedGraph::removeVertex(int vertex)
{
	if (m_adjacencyList.count(vertex))
	{
		m_adjacencyList.erase(vertex);
		for (auto i = m_adjacencyList.begin(); i != m_adjacencyList.end(); i++)
		{
			i->second.erase(std::remove_if(i->second.begin(), i->second.end(), [vertex](int x){ return vertex == x; }), i->second.end());
		}
	}
}

void UndirectedGraph::addEdge(int start, int end)
{
	if (!std::count(m_adjacencyList[start].begin(), m_adjacencyList[start].end(), end) &&
		!std::count(m_adjacencyList[end].begin(), m_adjacencyList[end].end(), start))
	{
		m_adjacencyList[start].emplace_back(end);
		m_adjacencyList[end].emplace_back(start);
	}
}

void UndirectedGraph::removeEdge(int start, int end)
{
	if (std::count(m_adjacencyList[start].begin(), m_adjacencyList[start].end(), end) &&
		std::count(m_adjacencyList[end].begin(), m_adjacencyList[end].end(), start))
	{
		m_adjacencyList[start].erase(std::remove_if(m_adjacencyList[start].begin(), m_adjacencyList[start].end(),
													[end](int x){ return x = end; }), m_adjacencyList[start].end());
		m_adjacencyList[end].erase(std::remove_if(m_adjacencyList[end].begin(), m_adjacencyList[end].end(),
												  [start](int x){ return x = start; }), m_adjacencyList[end].end());
	}
}

const std::vector<int>& UndirectedGraph::adjacentVertices(int vertex)
{
	return m_adjacencyList[vertex];
}

void UndirectedGraph::print()
{
	for (auto i = m_adjacencyList.begin(); i != m_adjacencyList.end(); i++)
	{
		std::cout << i->first << ": ";
		for (auto j = i->second.begin(); j != i->second.end(); j++)
		{
			std::cout << *j << ' ';
		}
		std::cout << '\n';
	}
}