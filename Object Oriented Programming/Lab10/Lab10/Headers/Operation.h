#pragma once

#include <functional>

class Operation
{
	public:
		Operation() = default;
		Operation(std::function<void()> undoFunction, std::function<void()> redoFunction) :
			m_undoFunction(undoFunction),
			m_redoFunction(redoFunction)
		{
						
		}

		void undo()
		{
			m_undoFunction();
		}

		void redo()
		{
			m_redoFunction();
		}
	private:
		std::function<void()> m_undoFunction;
		std::function<void()> m_redoFunction;
};