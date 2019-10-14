#pragma once

#include "Operation.h"

#include <stack>
#include <functional>
#include <string>
#include <vector>

class FunctionStack
{
	public:
		FunctionStack() :
			m_index(-1)
		{

		};

		void push(const Operation& operation)
		{
			m_index++;
			m_operations.emplace_back(operation);
		}

		void undo()
		{
			if (m_index >= 0 && m_index < m_operations.size())
			{
				m_operations[m_index].undo();
				m_index--;
			}
		}

		void redo()
		{
			m_index++;
			m_operations[m_index].redo();
		}
	private:
		std::vector<Operation> m_operations;
		int m_index;
};