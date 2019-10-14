#pragma once

#include "UndirectedGraph.h"

class Interface
{
	public:
		Interface();

		void run();
	private:
		UndirectedGraph g;
		bool running;
};