#pragma once

#include <map>
#include <set>
#include <string>
#include <fstream>
#include <typeinfo>
#include <type_traits>
#include <iostream>
#include <iterator>
#include <limits>
#include <queue>

#define MAX_COST 1000000000

template<typename VertexIndex, typename EdgeData = int>
class DirectedGraph
{
	public:
		DirectedGraph() = default;

		void readFromFile(const std::string& filepath);

		unsigned int getNumOfVertices() const;

		const bool isEdge(VertexIndex start, VertexIndex end) const;

		unsigned int inDegree(VertexIndex vertex);
		unsigned int outDegree(VertexIndex vertex);

		typename std::set<VertexIndex>::iterator iterator();
		typename std::set<VertexIndex>::iterator begin();
		typename std::set<VertexIndex>::iterator end();

		typename std::set<VertexIndex>::iterator inboundIterator();
		typename std::set<VertexIndex>::iterator inboundBegin(VertexIndex vertex);
		typename std::set<VertexIndex>::iterator inboundEnd(VertexIndex vertex);

		typename std::set<VertexIndex>::iterator outboundIterator();
		typename std::set<VertexIndex>::iterator outboundBegin(VertexIndex vertex);
		typename std::set<VertexIndex>::iterator outboundEnd(VertexIndex vertex);

		const EdgeData getEdgeData(VertexIndex start, VertexIndex end);
		void setEdgeData(VertexIndex start, VertexIndex end, const EdgeData data);

		void addVertex(VertexIndex vertex);
		void removeVertex(VertexIndex vertex);

		void addEdge(VertexIndex start, VertexIndex end);
		void removeEdge(VertexIndex start, VertexIndex end);

		std::map<VertexIndex, VertexIndex> dijkstra(int start, int end);

		void print() const;

	private:
		std::set<VertexIndex> m_vertices;
		std::map<VertexIndex, std::set<VertexIndex>> m_inboundVertices;
		std::map<VertexIndex, std::set<VertexIndex>> m_outboundVertices;
		std::map<std::pair<VertexIndex, VertexIndex>, EdgeData> m_edges;
		int m_num;
};

/*
	Reads data into a graph.
	Preconditions: filepath must be a valid filepath with data formatted in the correct way.
	Parameters:
		filepath - filepath which data will be read from
	Throws:
		std::exception - if the given filepath is invalid or the file could not be opened
*/
template<typename VertexIndex, typename EdgeData>
void DirectedGraph<typename VertexIndex, typename EdgeData>::readFromFile(const std::string& filepath)
{
	std::ifstream inputFile(filepath);
	int numOfVertices;
	int numOfEdges;
	if (!inputFile.good()) // check if file is valid
	{
		throw std::exception("Invalid file!");
	}
	inputFile >> numOfVertices; // read number of vertices
	m_num = numOfVertices;
	inputFile >> numOfEdges; // read number of edges
	for (int i = 0; i < numOfEdges; i++)
	{
		VertexIndex x, y;
		EdgeData d;
		inputFile >> x >> y >> d; // read edge data
		// only insert vertex/edge if it doesn't exist already
		if (!m_vertices.count(x))
		{
			m_vertices.insert(x);
		}
		if (!m_vertices.count(y))
		{
			m_vertices.insert(y);
		}
		m_outboundVertices[x].insert(y);
		m_inboundVertices[y].insert(x);
		m_edges.insert(std::make_pair(std::make_pair(x, y), d));
	}
	inputFile.close(); // close file
}

/*
	Returns the number of vertices in the graph.
	Return: the number of vertices in the graph.
*/
template<typename VertexIndex, typename EdgeData>
unsigned int DirectedGraph<typename VertexIndex, typename EdgeData>::getNumOfVertices() const
{
	return m_num;
}

/*
	Returns an iterator to the list of vertices.
*/
template<typename VertexIndex, typename EdgeData>
typename std::set<VertexIndex>::iterator DirectedGraph<typename VertexIndex, typename EdgeData>::iterator()
{
	return std::set<VertexIndex>::iterator();
}

/*
	Returns an iterator to the beginning of the list of vertices.
*/
template<typename VertexIndex, typename EdgeData>
typename std::set<VertexIndex>::iterator DirectedGraph<typename VertexIndex, typename EdgeData>::begin()
{
	return m_vertices.begin();
}

/*
	Returns an iterator to the end of the list of vertices.
*/
template<typename VertexIndex, typename EdgeData>
typename std::set<VertexIndex>::iterator DirectedGraph<typename VertexIndex, typename EdgeData>::end()
{
	return m_vertices.end();
}

/*
	Checks if a given edge exists.

*/
template<typename VertexIndex, typename EdgeData>
const bool DirectedGraph<typename VertexIndex, typename EdgeData>::isEdge(VertexIndex start, VertexIndex end) const
{
	return m_edges.count(std::make_pair(start, end)) != 0;
}

/*
	Returns the in degree of a given vertex.
	Preconditions: vertex must be a valid vertex in the graph.
	Parameters:
		vertex - vertex for which the in degree is returned
	Return: the in degere of a given vertex
*/
template<typename VertexIndex, typename EdgeData>
unsigned int DirectedGraph<typename VertexIndex, typename EdgeData>::inDegree(VertexIndex vertex)
{
	return m_inboundVertices[vertex].size();
}

/*
	Returns the out degree of a given vertex.
	Preconditions: vertex must be a valid vertex in the graph.
	Parameters:
		vertex - vertex for which the out degree is returned
	Return: the out degere of a given vertex
*/
template<typename VertexIndex, typename EdgeData>
unsigned int DirectedGraph<typename VertexIndex, typename EdgeData>::outDegree(VertexIndex vertex)
{
	return m_outboundVertices[vertex].size();
}

/*
	Returns an iterator to the inbound vertices.
*/
template<typename VertexIndex, typename EdgeData>
typename std::set<VertexIndex>::iterator DirectedGraph<typename VertexIndex, typename EdgeData>::inboundIterator()
{
	return std::set<VertexIndex>::iterator();
}

/*
	Returns an iterator to the beginning of the list of inbound vertices.
*/
template<typename VertexIndex, typename EdgeData>
typename std::set<VertexIndex>::iterator DirectedGraph<typename VertexIndex, typename EdgeData>::inboundBegin(VertexIndex vertex)
{
	return m_inboundVertices[vertex].begin();
}

/*
	Returns an iterator to the end of the list of inbound vertices.
*/
template<typename VertexIndex, typename EdgeData>
typename std::set<VertexIndex>::iterator DirectedGraph<typename VertexIndex, typename EdgeData>::inboundEnd(VertexIndex vertex)
{
	return m_inboundVertices[vertex].end();
}

/*
	Returns an iterator to the list of outbound vertices.
*/
template<typename VertexIndex, typename EdgeData>
typename std::set<VertexIndex>::iterator DirectedGraph<typename VertexIndex, typename EdgeData>::outboundIterator()
{
	return std::set<VertexIndex>::iterator();
}

/*
	Returns an iterator to the start of the list of the outbound vertices.
*/
template<typename VertexIndex, typename EdgeData>
typename std::set<VertexIndex>::iterator DirectedGraph<typename VertexIndex, typename EdgeData>::outboundBegin(VertexIndex vertex)
{
	return m_outboundVertices[vertex].begin();
}

/*
	Returns an iterator to the end of the list of outbound vertices.
*/
template<typename VertexIndex, typename EdgeData>
typename std::set<VertexIndex>::iterator DirectedGraph<typename VertexIndex, typename EdgeData>::outboundEnd(VertexIndex vertex)
{
	return m_outboundVertices[vertex].end();
}

/*
	Returns the data associated with an edge.
	Preconditions: (start, end) must be a valid edge in the graph.
	Parameters:
		start - start vertex of the edge
		end - end vertex of the edge
	Throws:
		std::exception - if the given edge doesn't exist in the graph.
*/
template<typename VertexIndex, typename EdgeData>
const EdgeData DirectedGraph<typename VertexIndex, typename EdgeData>::getEdgeData(VertexIndex start, VertexIndex end)
{
	if (!m_edges.count(std::make_pair(start, end)))
	{
		throw std::exception("No such edge exists!");
	}
	return m_edges[std::pair<VertexIndex, VertexIndex>(start, end)];
}

/*
	Sets the data of an edge.
	Preconditions: (start, end) must be a valid edge in the graph.
	Parameters:
		start - start vertex of the edge
		end - end vertex of the edge
		data - data for (start, end) to be set
	Throws:
		std::exception - if the given edge doesn't exist in the graph.
*/
template<typename VertexIndex, typename EdgeData>
void DirectedGraph<typename VertexIndex, typename EdgeData>::setEdgeData(VertexIndex start, VertexIndex end, const EdgeData data)
{
	if (!m_edges.count(std::make_pair(start, end)))
	{
		throw std::exception("No such edge exists!");
	}
	m_edges[std::make_pair(start, end)] = data;
}

/*
	Adds a vertex to the graph.
	Preconditions: vertex must not already exist in the graph.
	Parameters:
		vertex - vertex to be added to the graph
	Throws:
		std::exception - if the given vertex already exists in the graph.
*/
template<typename VertexIndex, typename EdgeData>
void DirectedGraph<typename VertexIndex, typename EdgeData>::addVertex(VertexIndex vertex)
{
	if (m_vertices.count(vertex))
	{
		throw std::exception("Vertex already exists!");
	}
	m_vertices.insert(vertex);
	m_inboundVertices.insert(std::make_pair(vertex, std::set<VertexIndex>()));
	m_outboundVertices.insert(std::make_pair(vertex, std::set<VertexIndex>()));
	m_num++;
}

/*
	Remove a vertex from the graph.
	Preconditions: vertex must exist in the graph.
	Parameters:
		vertex - vertex to be removed
	Throws:
		std::exception - if the given vertex doesn't exist in the graph.
*/
template<typename VertexIndex, typename EdgeData>
void DirectedGraph<typename VertexIndex, typename EdgeData>::removeVertex(VertexIndex vertex)
{
if (!m_vertices.count(vertex))
{
	throw std::exception("No vertex with given ID exists!");
}
m_num--;
m_vertices.erase(vertex);
for (auto it = m_inboundVertices.begin(); it != m_inboundVertices.end(); it++)
{
	it->second.erase(vertex);
}
m_outboundVertices.erase(vertex);
for (auto it = m_edges.begin(); it != m_edges.end();)
{
	if (it->first.first == vertex || it->first.second == vertex)
	{
		m_edges.erase(it++);
	}
	else
	{
		++it;
	}
}
}

/*
	Adds an edge with endpoints start and end to the graph.
	Preconditions: (start, end) must not already exist in the graph.
	Parameters:
		start - start vertex of the edge to add
		end - end vertex of the edge to add
	Throws:
		std::exception - if the given edge already exists in the graph.
*/
template<typename VertexIndex, typename EdgeData>
void DirectedGraph<typename VertexIndex, typename EdgeData>::addEdge(VertexIndex start, VertexIndex end)
{
	if (m_edges.count(std::make_pair(start, end)))
	{
		throw std::exception("Edge alerady exists!");
	}
	m_inboundVertices[end].insert(start);
	m_outboundVertices[start].insert(end);
	m_edges.insert(std::make_pair(std::make_pair(start, end), -1));
}

/*
	Removes an edge with endpoints start and end from the graph.
	Preconditions: (start, end) must  exist in the graph.
	Parameters:
		start - start vertex of the edge to remove
		end - end vertex of the edge to remove
	Throws:
		std::exception - if the given edge doesn't exist in the graph.
*/
template<typename VertexIndex, typename EdgeData>
void DirectedGraph<typename VertexIndex, typename EdgeData>::removeEdge(VertexIndex start, VertexIndex end)
{
	if (!m_edges.count(std::make_pair(start, end)))
	{
		throw std::exception("No edge with given ends exists!");
	}
	m_inboundVertices[end].erase(start);
	m_outboundVertices[start].erase(end);
	m_edges.erase(std::make_pair(start, end));
}

template<typename VertexIndex, typename EdgeData>
std::map<VertexIndex, VertexIndex> DirectedGraph<typename VertexIndex, typename EdgeData>::dijkstra(int start, int end)
{
	std::map<VertexIndex, EdgeData> best;
	std::map<VertexIndex, bool> visited;
	std::map<VertexIndex, VertexIndex> parents;

	for (int i = 0; i < m_num; i++)
	{
		if (i != end)
		{
			EdgeData cost;
			try
			{
				cost = getEdgeData(i, end);
			}
			catch (...)
			{
				cost = MAX_COST;
			}
			best[i] = cost;
			visited[i] = false;
		}
		parents[i] = -1;
	}

	visited[end] = true;

	for(auto i = best.begin(); i != best.end(); i++)
	{
		std::pair<VertexIndex, EdgeData> min{ MAX_COST, MAX_COST };
		for (auto j = best.begin(); j != best.end(); j++)
		{
			if (!visited[j->first] && j->second < min.second)
			{
				min = *j;
			}
		}
		visited[min.first] = true;
		for (auto j = m_vertices.begin(); j != m_vertices.end(); j++)
		{
			EdgeData cost;
			try
			{
				cost = getEdgeData(*j, min.first);
			}
			catch (...)
			{
				cost = MAX_COST;
			}
			if (!visited[*j] && best[min.first] + cost < best[*j])
			{
				best[*j] = best[min.first] + cost;
				parents[*j] = min.first;
			}
		}
	}

	while (parents[start] != -1)
	{
		start = parents[start];
	}

	parents[start] = end;

	return parents;
}

template<typename VertexIndex, typename EdgeData>
void DirectedGraph<typename VertexIndex, typename EdgeData>::print() const
{
	std::cout << "Vertices:" << '\n';
	for (auto v : m_vertices)
	{
		std::cout << v << ' ';
	}
	std::cout << '\n';

	std::cout << "Edges" << '\n';

	for (auto& edge : m_edges)
	{
		std::cout << edge.first.first << ", " << edge.first.second << " : " << edge.second << '\n';
	}
}