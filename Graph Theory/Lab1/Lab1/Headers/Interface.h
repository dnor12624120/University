#pragma once

#include "DirectedGraph.h"

class Interface
{
	public:
		Interface();

		void run();
	private:
		void readFromFile();
		void numOfvertices();
		void isEdge();
		void inDegree();
		void outDegree();
		void getEdgeData();
		void setEdgeData();
		void addVertex();
		void removeVertex();
		void addEdge();
		void removeEdge();
		void inboundEdges();
		void outboundEdges();
		void print();

	DirectedGraph<int, int> m_graph;
	bool m_running;
};