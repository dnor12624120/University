#include "Interface.h"

#include <iostream>
#include <string>

#define NUMBER_OF_COMMANDS 14

Interface::Interface() :
	m_graph(DirectedGraph<int, int>()),
	m_running(true)
{

}

void Interface::run()
{
	m_graph.readFromFile("test.txt");
	std::cout << " 0. Exit\n";
	std::cout << " 1. Read From File\n";
	std::cout << " 2. Get Number Of Vertices\n";
	std::cout << " 3. Is Edge\n";
	std::cout << " 4. In Degree\n";
	std::cout << " 5. Out Degree\n";
	std::cout << " 6. Get Edge Data\n";
	std::cout << " 7. Set Edge Data\n";
	std::cout << " 8. Add Vertex\n";
	std::cout << " 9. Remove Vertex\n";
	std::cout << "10. Add Edge\n";
	std::cout << "11. Remove Edge\n";
	std::cout << "12. Inbound Edges\n";
	std::cout << "13. Outbound Edges\n";
	std::cout << "14. Print\n";

	while (m_running)
	{
		int command;
		std::cout << ">";
		std::cin >> command;
		if (command < 0 || command > NUMBER_OF_COMMANDS)
		{
			std::cout << "Invalid command!\n";
		}
		switch (command)
		{
			case 0:
			{
				m_running = false;
				break;
			}
			case 1:
			{
				readFromFile();
				break;
			}
			case 2:
			{
				numOfvertices();
				break;
			}
			case 3:
			{
				isEdge();
				break;
			}
			case 4:
			{
				inDegree();
				break;
			}
			case 5:
			{
				outDegree();
				break;
			}
			case 6:
			{
				getEdgeData();
				break;
			}
			case 7:
			{
				setEdgeData();
				break;
			}
			case 8:
			{
				addVertex();
				break;
			}
			case 9:
			{
				removeVertex();
				break;
			}
			case 10:
			{
				addEdge();
				break;
			}
			case 11:
			{
				removeEdge();
				break;
			}
			case 12:
			{
				inboundEdges();
				break;
			}
			case 13:
			{
				outboundEdges();
				break;
			}
			case 14:
			{
				print();
				break;
			}
		}
	}
}

void Interface::readFromFile()
{
	std::string filepath;
	std::cout << ">";
	std::cin >> filepath;
	try
	{
		m_graph.readFromFile(filepath);
		std::cout << "Data read successfully!\n";
	}
	catch(std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
}

void Interface::numOfvertices()
{
	try
	{
		std::cout << m_graph.getNumOfVertices() << '\n';
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
}
void Interface::isEdge()
{
	int x, y;
	std::cin >> x >> y;
	try
	{
		if (m_graph.isEdge(x, y))
		{
			std::cout << "Edge exists!\n";
		}
		else
		{
			std::cout << "Edge does not exist!\n";
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
}

void Interface::inDegree()
{
	int x;
	std::cin >> x;
	try
	{
		std::cout << m_graph.inDegree(x) << '\n';
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
}

void Interface::outDegree()
{
	int x;
	std::cin >> x;
	try
	{
		std::cout << m_graph.outDegree(x) << '\n';
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
}

void Interface::getEdgeData()
{
	int x, y;
	std::cin >> x >> y;
	try
	{
		std::cout << m_graph.getEdgeData(x, y) << '\n';
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
}

void Interface::setEdgeData()
{
	int x, y, data;
	std::cin >> x >> y >> data;
	try
	{
		m_graph.setEdgeData(x, y, data);
		std::cout << "Data updated successfully!\n";
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
}

void Interface::addVertex()
{
	int v;
	std::cin >> v;
	try
	{
		m_graph.addVertex(v);
		std::cout << "Vertex added successfully!\n";
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
}

void Interface::removeVertex()
{
	int v;
	std::cin >> v;
	try
	{
		std::cout << "Vertex removed successfully!\n";
		m_graph.removeVertex(v);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
}

void Interface::addEdge()
{
	int x, y;
	std::cin >> x >> y;
	try
	{
		m_graph.addEdge(x, y);
		std::cout << "Edge added successfully!\n";
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
}

void Interface::removeEdge()
{
	int x, y;
	std::cin >> x >> y;
	try
	{
		m_graph.removeEdge(x, y);
		std::cout << "Edge removed successfully!\n";
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
}

void Interface::inboundEdges()
{
	int x;
	std::cout << ">";
	std::cin >> x;
	for (auto list = m_graph.inboundBegin(x); list != m_graph.inboundEnd(x); list++)
	{
		std::cout << *list << '\n';
	}
}

void Interface::outboundEdges()
{
	int x;
	std::cout << ">";
	std::cin >> x;
	for (auto list = m_graph.outboundBegin(x); list != m_graph.outboundEnd(x); list++)
	{
		std::cout << *list << '\n';
	}
}

void Interface::print()
{
	m_graph.print();
}