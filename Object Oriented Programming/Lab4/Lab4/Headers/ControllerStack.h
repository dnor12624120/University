#pragma once

#include "Controller.h"


typedef struct ControllerStack ControllerStack;
typedef struct ControllerFunction ControllerFunction;

#define CONTROLLER_STACK_ERROR -1
#define CONTROLLER_STACK_SUCCESS 0

/*
	Constructor for ControllerStack.
	Returns CONTROLLER_STACK_SUCCESS in case of a successful allocation (*controllerStack must be valid),
	or CONTROLLER_STACK_ERROR otherwise
*/
int ControllerStack_Create(ControllerStack** controllerStack);

/*
	Destructor for ControllerStack.
	Returns CONTROLLER_STACK_SUCCESS in case of a successful deallocation (*controllerStack must be valid),
	or CONTROLLER_STACK_ERROR otherwise
*/
int ControllerStack_Destroy(ControllerStack** controllerStack);

/*
	Adds a ControllerFunction object to the stack, containing information needed for undoing/redoing a
	function called by the interface. Returns CONTROLLER_STACK_ERROR if pointer arguments are invalid,
	or CONTROLLER_STACK_SUCCESS otherwise.
*/
int ControllerStack_AddFunction(ControllerStack* controllerStack,
								int(*undoFunction)(Controller* controller, int argumentCount, char** argumentVector, int addToStack),
								int undoArgumentCount, char** undoArgumentVector,
								int(*redoFunction)(Controller* controller, int argumentCount, char** argumentVector, int addToStack),
								int redoArgumentCount, char** redoArgumentVector);

/*
	Undoes the last operation on the stack.
*/
int ControllerStack_Undo(ControllerStack* controllerStack, Controller* controller);

/*
	Redoes the last operation on the stack.
*/
int ControllerStack_Redo(ControllerStack* controllerStack, Controller* controller);

