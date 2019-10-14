#include "ControllerStack.h"

#include <stdlib.h>

#define CONTROLLER_STACK_MAX_SIZE 512

#define CONTROLLER_STACK_ERROR -1
#define CONTROLLER_STACK_SUCCESS 0

struct ControllerFunction
{
	int(*UndoFunction)(Controller* controller, int argumentCount, char** argumentVector, int addToStack);
	int(*RedoFunction)(Controller* controller, int argumentCount, char** argumentVector, int addToStack);
	int UndoArgumentCount;
	int RedoArgumentCount;
	char** UndoArgumentVector;
	char** RedoArgumentVector;
};

struct ControllerStack
{
	ControllerFunction Stack[CONTROLLER_STACK_MAX_SIZE];
	int Top;
	int Size;
};

int ControllerStack_Create(ControllerStack** controllerStack)
{
	ControllerStack* tempControllerStack = malloc(sizeof(ControllerStack));
	if (tempControllerStack == NULL)
	{
		return CONTROLLER_STACK_ERROR;
	}
	tempControllerStack->Top = -1;
	tempControllerStack->Size = 0;
	memset(tempControllerStack->Stack, 0, sizeof(tempControllerStack->Stack));
	*controllerStack = tempControllerStack;
	return CONTROLLER_STACK_SUCCESS;
}

int ControllerStack_Destroy(ControllerStack** controllerStack)
{
	ControllerStack* tempControllerStack = *controllerStack;
	if (tempControllerStack == NULL)
	{
		return CONTROLLER_STACK_ERROR;
	}
	for (int i = 0; i < tempControllerStack->Size; i++)
	{
		for (int j = 0; j < tempControllerStack->Stack[i].UndoArgumentCount; j++)
		{
			free(tempControllerStack->Stack[i].UndoArgumentVector[j]);
		}
		free(tempControllerStack->Stack[i].UndoArgumentVector);
		tempControllerStack->Stack[i].UndoArgumentCount = 0;
		for (int j = 0; j < tempControllerStack->Stack[i].RedoArgumentCount; j++)
		{
			free(tempControllerStack->Stack[i].RedoArgumentVector[j]);
		}
		free(tempControllerStack->Stack[i].RedoArgumentVector);
		tempControllerStack->Stack[i].RedoArgumentCount = 0;
	}
	memset(tempControllerStack->Stack, 0, sizeof(tempControllerStack->Stack));
	tempControllerStack->Top = -1;
	tempControllerStack->Size = 0;
	free(tempControllerStack);
	tempControllerStack = NULL;
	return CONTROLLER_STACK_SUCCESS;
}

int ControllerStack_AddFunction(ControllerStack* controllerStack,
								int(*undoFunction)(Controller* controller, int argumentCount, char** argumentVector, int addToStack),
								int undoArgumentCount, char** undoArgumentVector,
								int(*redoFunction)(Controller* controller, int argumentCount, char** argumentVector, int addToStack),
								int redoArgumentCount, char** redoArgumentVector)
{
	if (controllerStack == NULL)
	{
		return CONTROLLER_STACK_ERROR;
	}
	if (undoFunction == NULL)
	{
		return CONTROLLER_STACK_ERROR;
	}
	if (redoFunction == NULL)
	{
		return CONTROLLER_STACK_ERROR;
	}
	if (controllerStack->Top == CONTROLLER_STACK_MAX_SIZE - 1)
	{
		return CONTROLLER_STACK_ERROR;
	}
	ControllerFunction controllerFunction = (ControllerFunction)
	{
		.UndoFunction = undoFunction,
		.UndoArgumentCount = undoArgumentCount,
		.UndoArgumentVector = undoArgumentVector,
		.RedoFunction = redoFunction,
		.RedoArgumentCount = redoArgumentCount,
		.RedoArgumentVector = redoArgumentVector
	};
	controllerStack->Top++;
	controllerStack->Stack[controllerStack->Size++] = controllerFunction;
	return CONTROLLER_STACK_SUCCESS;
}

int ControllerStack_Undo(ControllerStack* controllerStack, Controller* controller)
{
	if (controllerStack == NULL)
	{
		return CONTROLLER_STACK_ERROR;
	}
	if (controller == NULL)
	{
		return CONTROLLER_STACK_ERROR;
	}
	if (controllerStack->Top < 0)
	{
		return CONTROLLER_STACK_ERROR;
	}
	controllerStack->Stack[controllerStack->Top].UndoFunction(controller,
															  controllerStack->Stack[controllerStack->Top].UndoArgumentCount,
															  controllerStack->Stack[controllerStack->Top].UndoArgumentVector,
															  0);
	controllerStack->Top--;
	return CONTROLLER_STACK_SUCCESS;
}

int ControllerStack_Redo(ControllerStack* controllerStack, Controller* controller)
{
	if (controllerStack == NULL)
	{
		return CONTROLLER_STACK_ERROR;
	}
	if (controller == NULL)
	{
		return CONTROLLER_STACK_ERROR;
	}
	if (controllerStack->Top == controllerStack->Size - 1)
	{
		return CONTROLLER_STACK_ERROR;
	}
	controllerStack->Top++;
	controllerStack->Stack[controllerStack->Top].RedoFunction(controller,
															  controllerStack->Stack[controllerStack->Top].RedoArgumentCount,
															  controllerStack->Stack[controllerStack->Top].RedoArgumentVector,
															  0);
	return CONTROLLER_STACK_SUCCESS;
}



