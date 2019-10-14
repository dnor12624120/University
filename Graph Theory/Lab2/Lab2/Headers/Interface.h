#pragma once

#include "UndirectedGraph.h"

class Interface
{
	public:
		Interface();

		void run();
		void readFromFile();
		void addVertex();
		void removeVertex();
		void addEdge();
		void removeEdge();
		void getConnectedComponents();
		void print();
	private:
		bool m_running;
		UndirectedGraph graph;
};