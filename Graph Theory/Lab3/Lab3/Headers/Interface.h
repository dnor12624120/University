#pragma once

#include "DirectedGraph.h"

class Interface
{
	public:
		Interface();

		void run();
	private:
		DirectedGraph<int, int> g;
		bool running;
};