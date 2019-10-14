#include "Controller.h"
#include "ControllerStack.h"

#define CONTROLLER_ADD_BOT_SERIAL_INDEX 1
#define CONTROLLER_ADD_BOT_STATE_INDEX 2
#define CONTROLLER_ADD_BOT_SPECIALIZATION_INDEX 3
#define CONTROLLER_ADD_BOT_CAPACITY_INDEX 4
#define CONTROLLER_REMOVE_BOT_SERIAL_INDEX 1
#define CONTROLLER_UPDATE_BOT_SERIAL_INDEX 1
#define CONTROLLER_UPDATE_BOT_NEW_STATE_INDEX 2
#define CONTROLLER_UPDATE_BOT_NEW_SPECIALIZATION_INDEX 3
#define CONTROLLER_UPDATE_BOT_NEW_CAPACITY_INDEX 4

#define CONTROLLER_ADD_BOT_ARGUMENT_COUNT 4
#define CONTROLLER_UPDATE_BOT_ARGUMENT_COUNT 4
#define CONTROLLER_REMOVE_BOT_ARGUMENT_COUNT 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Controller
{
	Repository* Repository;
	ControllerStack* FunctionStack;
};

/*
	Controller-only function for converting a given string to an integer.
*/
static int ConvertStringToInt(const char* string);

/*
	Controller-only function for  converting a given integer to a string.
*/
static const char* ConvertIntToString(int number);

static int ReverseNumber(int number)
{
	int reverse = 0;
	while (number)
	{
		reverse = reverse * 10 + number % 10;
		number /= 10;
	}
	return reverse;
}

int Controller_Create(Controller** controller)
{
	Controller* tempController = malloc(sizeof(Controller));
	if (tempController == NULL)
	{
		return CONTROLLER_ERROR;
	}
	tempController->Repository = NULL;
	ControllerStack_Create(&(tempController->FunctionStack));
	*controller = tempController;
	return CONTROLLER_SUCCESS;
}

int Controller_Destroy(Controller** controller)
{
	Controller* tempController = *controller;
	if (tempController == NULL)
	{
		return CONTROLLER_ERROR;
	}
	Repository_Destroy(&(tempController->Repository));
	ControllerStack_Destroy(&(tempController->FunctionStack));
	tempController = NULL;
	controller = NULL;
	return CONTROLLER_SUCCESS;
}

int Controller_Init(Controller* controller, Repository* repository)
{
	if (controller == NULL)
	{
		return CONTROLLER_ERROR;
	}
	if (repository == NULL)
	{
		return CONTROLLER_ERROR;
	}
	controller->Repository = repository;
	return CONTROLLER_SUCCESS;
}

int Controller_AddBot(Controller* controller, int argumentCount, char** argumentVector, int addToStack)
{
	if (controller == NULL)
	{
		return CONTROLLER_ERROR;
	}
	if (addToStack)
	{
		// The function was called from the interface, so we need to add it to the function stack so we can undo/redo it
		// Copy arguments we need for the undo function for add (remove)
		char** undoArgumentVector = malloc((CONTROLLER_REMOVE_BOT_ARGUMENT_COUNT + 1) * sizeof(char*));
		undoArgumentVector[CONTROLLER_REMOVE_BOT_SERIAL_INDEX] = malloc(strlen(argumentVector[CONTROLLER_ADD_BOT_SERIAL_INDEX]) + 1);
		strcpy_s(undoArgumentVector[CONTROLLER_REMOVE_BOT_SERIAL_INDEX], strlen(argumentVector[CONTROLLER_ADD_BOT_SERIAL_INDEX]) + 1,
				 argumentVector[CONTROLLER_ADD_BOT_SERIAL_INDEX]);
		// Copy arguments we need for the redo function for add (add)
		char** redoArgumentVector = malloc((CONTROLLER_ADD_BOT_ARGUMENT_COUNT + 1) * sizeof(char*));
		redoArgumentVector[CONTROLLER_ADD_BOT_SERIAL_INDEX] = malloc(strlen(argumentVector[CONTROLLER_ADD_BOT_SERIAL_INDEX]) + 1);
		redoArgumentVector[CONTROLLER_ADD_BOT_STATE_INDEX] = malloc(strlen(argumentVector[CONTROLLER_ADD_BOT_STATE_INDEX]) + 1);
		redoArgumentVector[CONTROLLER_ADD_BOT_SPECIALIZATION_INDEX] = malloc(strlen(argumentVector[CONTROLLER_ADD_BOT_SPECIALIZATION_INDEX]) + 1);
		redoArgumentVector[CONTROLLER_ADD_BOT_CAPACITY_INDEX] = malloc(strlen(argumentVector[CONTROLLER_ADD_BOT_CAPACITY_INDEX]) + 1);
		strcpy_s(redoArgumentVector[CONTROLLER_ADD_BOT_SERIAL_INDEX], strlen(argumentVector[CONTROLLER_ADD_BOT_SERIAL_INDEX]) + 1,
				 argumentVector[CONTROLLER_ADD_BOT_SERIAL_INDEX]);
		strcpy_s(redoArgumentVector[CONTROLLER_ADD_BOT_STATE_INDEX], strlen(argumentVector[CONTROLLER_ADD_BOT_STATE_INDEX]) + 1,
				 argumentVector[CONTROLLER_ADD_BOT_STATE_INDEX]);
		strcpy_s(redoArgumentVector[CONTROLLER_ADD_BOT_SPECIALIZATION_INDEX], strlen(argumentVector[CONTROLLER_ADD_BOT_SPECIALIZATION_INDEX]) + 1,
				 argumentVector[CONTROLLER_ADD_BOT_SPECIALIZATION_INDEX]);
		strcpy_s(redoArgumentVector[CONTROLLER_ADD_BOT_CAPACITY_INDEX], strlen(argumentVector[CONTROLLER_ADD_BOT_CAPACITY_INDEX]) + 1,
				 argumentVector[CONTROLLER_ADD_BOT_CAPACITY_INDEX]);
		// Add the function to the function stack
		ControllerStack_AddFunction(controller->FunctionStack, Controller_DeleteBot, CONTROLLER_REMOVE_BOT_ARGUMENT_COUNT,
									undoArgumentVector, Controller_AddBot, CONTROLLER_ADD_BOT_ARGUMENT_COUNT,
									redoArgumentVector);
	}
	Bot* bot = NULL;
	Bot_Create(&bot);
	Bot_Init(bot, argumentVector[CONTROLLER_ADD_BOT_STATE_INDEX],
			      argumentVector[CONTROLLER_ADD_BOT_SPECIALIZATION_INDEX],
			      argumentVector[CONTROLLER_ADD_BOT_SERIAL_INDEX],
				  ConvertStringToInt(argumentVector[CONTROLLER_ADD_BOT_CAPACITY_INDEX]));
	Repository_AddBot(controller->Repository, bot);
	return CONTROLLER_SUCCESS;
}

int Controller_UpdateBot(Controller* controller, int argumentCount, char** argumentVector, int addToStack)
{
	if (controller == NULL)
	{
		return CONTROLLER_ERROR;
	}
	if (addToStack)
	{
		// The function was called from the interface, so we need to add it to the function stack so we can undo/redo it
		// Copy arguments we need for the undo function for update (update with the original fields)
		Bot* bot = Controller_GetBot(controller, argumentVector[CONTROLLER_UPDATE_BOT_SERIAL_INDEX]);
		if (bot)
		{
			const char* oldState = Bot_GetState(bot);
			const char* oldSpecialization = Bot_GetSpecialization(bot);
			const char* oldCapacity = _strrev(ConvertIntToString(Bot_GetCapacity(bot)));
			char** undoArgumentVector = malloc((CONTROLLER_UPDATE_BOT_ARGUMENT_COUNT + 1) * sizeof(char*));
			undoArgumentVector[CONTROLLER_UPDATE_BOT_SERIAL_INDEX] = malloc(strlen(argumentVector[CONTROLLER_UPDATE_BOT_SERIAL_INDEX]) + 1);
			undoArgumentVector[CONTROLLER_UPDATE_BOT_NEW_STATE_INDEX] = malloc(strlen(oldState) + 1);
			undoArgumentVector[CONTROLLER_UPDATE_BOT_NEW_SPECIALIZATION_INDEX] = malloc(strlen(oldSpecialization) + 1);
			undoArgumentVector[CONTROLLER_UPDATE_BOT_NEW_CAPACITY_INDEX] = malloc(strlen(oldCapacity) + 1);
			strcpy_s(undoArgumentVector[CONTROLLER_UPDATE_BOT_SERIAL_INDEX], strlen(argumentVector[CONTROLLER_UPDATE_BOT_SERIAL_INDEX]) + 1,
				   argumentVector[CONTROLLER_UPDATE_BOT_SERIAL_INDEX]);
			strcpy_s(undoArgumentVector[CONTROLLER_UPDATE_BOT_NEW_STATE_INDEX], strlen(oldState) + 1,
				   oldState);
			strcpy_s(undoArgumentVector[CONTROLLER_UPDATE_BOT_NEW_SPECIALIZATION_INDEX], strlen(oldSpecialization) + 1,
				   oldSpecialization);
			strcpy_s(undoArgumentVector[CONTROLLER_UPDATE_BOT_NEW_CAPACITY_INDEX], strlen(oldCapacity) + 1,
				   oldCapacity);
			free(oldCapacity);
			// Copy arguments we need for the redo function for update (update with the new fields)
			char** redoArgumentVector = malloc((CONTROLLER_UPDATE_BOT_ARGUMENT_COUNT + 1) * sizeof(char*));
			redoArgumentVector[CONTROLLER_UPDATE_BOT_SERIAL_INDEX] = malloc(strlen(argumentVector[CONTROLLER_UPDATE_BOT_SERIAL_INDEX]) + 1);
			redoArgumentVector[CONTROLLER_UPDATE_BOT_NEW_STATE_INDEX] = malloc(strlen(argumentVector[CONTROLLER_UPDATE_BOT_NEW_STATE_INDEX]) + 1);
			redoArgumentVector[CONTROLLER_UPDATE_BOT_NEW_SPECIALIZATION_INDEX] = malloc(strlen(argumentVector[CONTROLLER_UPDATE_BOT_NEW_SPECIALIZATION_INDEX]) + 1);
			redoArgumentVector[CONTROLLER_UPDATE_BOT_NEW_CAPACITY_INDEX] = malloc(strlen(argumentVector[CONTROLLER_UPDATE_BOT_NEW_CAPACITY_INDEX]) + 1);
			strcpy_s(redoArgumentVector[CONTROLLER_UPDATE_BOT_SERIAL_INDEX], strlen(argumentVector[CONTROLLER_UPDATE_BOT_SERIAL_INDEX]) + 1,
				   argumentVector[CONTROLLER_UPDATE_BOT_SERIAL_INDEX]);
			strcpy_s(redoArgumentVector[CONTROLLER_UPDATE_BOT_NEW_STATE_INDEX], strlen(argumentVector[CONTROLLER_UPDATE_BOT_NEW_STATE_INDEX]) + 1,
				   argumentVector[CONTROLLER_UPDATE_BOT_NEW_STATE_INDEX]);
			strcpy_s(redoArgumentVector[CONTROLLER_UPDATE_BOT_NEW_SPECIALIZATION_INDEX], strlen(argumentVector[CONTROLLER_UPDATE_BOT_NEW_SPECIALIZATION_INDEX]) + 1,
				   argumentVector[CONTROLLER_UPDATE_BOT_NEW_SPECIALIZATION_INDEX]);
			strcpy_s(redoArgumentVector[CONTROLLER_UPDATE_BOT_NEW_CAPACITY_INDEX], strlen(argumentVector[CONTROLLER_UPDATE_BOT_NEW_CAPACITY_INDEX]) + 1,
				   argumentVector[CONTROLLER_UPDATE_BOT_NEW_CAPACITY_INDEX]);
			ControllerStack_AddFunction(controller->FunctionStack, Controller_UpdateBot, CONTROLLER_UPDATE_BOT_ARGUMENT_COUNT,
										undoArgumentVector, Controller_UpdateBot, CONTROLLER_UPDATE_BOT_ARGUMENT_COUNT, redoArgumentVector);
		}
	}
	Repository_UpdateBot(controller->Repository,
						 argumentVector[CONTROLLER_UPDATE_BOT_SERIAL_INDEX],
						 argumentVector[CONTROLLER_UPDATE_BOT_NEW_STATE_INDEX],
						 argumentVector[CONTROLLER_UPDATE_BOT_NEW_SPECIALIZATION_INDEX],
						 ConvertStringToInt(argumentVector[CONTROLLER_UPDATE_BOT_NEW_CAPACITY_INDEX]));
	return CONTROLLER_SUCCESS;
}

int Controller_DeleteBot(Controller* controller, int argumentCount, char** argumentVector, int addToStack)
{
	if (controller == NULL)
	{
		return CONTROLLER_ERROR;
	}
	if (addToStack)
	{
		// The function was called from the interface, so we need to add it to the function stack so we can undo/redo it
		// Copy arguments we need for the undo function for remove (add)
		Bot* bot = Controller_GetBot(controller, argumentVector[CONTROLLER_REMOVE_BOT_SERIAL_INDEX]);
		if (bot)
		{
			const char* oldState = Bot_GetState(bot);
			const char* oldSpecialization = Bot_GetSpecialization(bot);
			const char* oldCapacity = _strrev(ConvertIntToString(Bot_GetCapacity(bot)));
			char** undoArgumentVector = malloc((CONTROLLER_ADD_BOT_ARGUMENT_COUNT + 1) * sizeof(char*));
			undoArgumentVector[CONTROLLER_ADD_BOT_SERIAL_INDEX] = malloc(strlen(argumentVector[CONTROLLER_ADD_BOT_SERIAL_INDEX]) + 1);
			undoArgumentVector[CONTROLLER_ADD_BOT_STATE_INDEX] = malloc(strlen(oldState) + 1);
			undoArgumentVector[CONTROLLER_ADD_BOT_SPECIALIZATION_INDEX] = malloc(strlen(oldSpecialization) + 1);
			undoArgumentVector[CONTROLLER_ADD_BOT_CAPACITY_INDEX] = malloc(strlen(oldCapacity) + 1);
			strcpy_s(undoArgumentVector[CONTROLLER_ADD_BOT_SERIAL_INDEX], strlen(argumentVector[CONTROLLER_ADD_BOT_SERIAL_INDEX]) + 1,
					 argumentVector[CONTROLLER_ADD_BOT_SERIAL_INDEX]);
			strcpy_s(undoArgumentVector[CONTROLLER_ADD_BOT_STATE_INDEX], strlen(oldState) + 1,
					 oldState);
			strcpy_s(undoArgumentVector[CONTROLLER_ADD_BOT_SPECIALIZATION_INDEX], strlen(oldSpecialization) + 1,
					 oldSpecialization);
			strcpy_s(undoArgumentVector[CONTROLLER_ADD_BOT_CAPACITY_INDEX], strlen(oldCapacity) + 1,
					 oldCapacity);
			free(oldCapacity);
			// Copy arguments we need for the redo function for remove (remove)
			char** redoArgumentVector = malloc((CONTROLLER_REMOVE_BOT_ARGUMENT_COUNT + 1) * sizeof(char*));
			redoArgumentVector[CONTROLLER_REMOVE_BOT_SERIAL_INDEX] = malloc(strlen(argumentVector[CONTROLLER_REMOVE_BOT_SERIAL_INDEX]) + 1);
			strcpy_s(redoArgumentVector[CONTROLLER_REMOVE_BOT_SERIAL_INDEX], strlen(argumentVector[CONTROLLER_REMOVE_BOT_SERIAL_INDEX]) + 1,
				   argumentVector[CONTROLLER_REMOVE_BOT_SERIAL_INDEX]);
			ControllerStack_AddFunction(controller->FunctionStack, Controller_AddBot, CONTROLLER_ADD_BOT_ARGUMENT_COUNT,
										undoArgumentVector, Controller_DeleteBot, CONTROLLER_REMOVE_BOT_ARGUMENT_COUNT, undoArgumentVector);
		}
	}
	Repository_DeleteBot(controller->Repository,
						 argumentVector[CONTROLLER_REMOVE_BOT_SERIAL_INDEX]);
	return CONTROLLER_SUCCESS;
}

Bot* Controller_GetBot(Controller* controller, const char* serialNumber)
{
	if (controller == NULL)
	{
		return NULL;
	}
	return Repository_GetBot(controller->Repository, serialNumber);
}

Bot** Controller_FilterBotSpecialization(Controller* controller, int* filterSize, const char* specialization, int(*filter)(Bot* bot, const char* specialization))
{
	if (controller == NULL)
	{
		return NULL;
	}
	return Repository_FilterBotSpecialization(controller->Repository, filterSize, specialization, filter);
}

Bot** Controller_FilterBotCapacity(Controller* controller, int* filterSize, int capacity, int(*filter)(Bot* bot, int capacity))
{
	if (controller == NULL)
	{
		return NULL;
	}
	return Repository_FilterBotCapacity(controller->Repository, filterSize, capacity, filter);
}

Bot** Controller_SortBots(Bot** bots, int listSize, int(*comparisonFunction)(Bot* bot1, Bot* bot2))
{
	if (bots == NULL)
	{
		return NULL;
	}
	return Repository_SortBots(bots, listSize, comparisonFunction);
}


int Controller_Undo(Controller* controller)
{
	if (controller == NULL)
	{
		return CONTROLLER_ERROR;
	}
	if (ControllerStack_Undo(controller->FunctionStack, controller) == CONTROLLER_STACK_ERROR)
	{
		return CONTROLLER_ERROR;
	}
	return CONTROLLER_SUCCESS;
}

int Controller_Redo(Controller* controller)
{
	if (controller == NULL)
	{
		return CONTROLLER_ERROR;
	}
	if (ControllerStack_Redo(controller->FunctionStack, controller) == CONTROLLER_STACK_ERROR)
	{
		return CONTROLLER_ERROR;
	}
	return CONTROLLER_SUCCESS;
}

static int ConvertStringToInt(const char* string)
{
	int convertedNumber = 0;
	for (int i = 0; string[i]; i++)
	{
		convertedNumber = convertedNumber * 10 + string[i] - '0';
	}
	return convertedNumber;
}

static const char* ConvertIntToString(int number)
{
	char* convertedString = malloc(10);
	int i = 0;
	for (i = 0; number; i++)
	{
		convertedString[i] = (number % 10) + '0';
		number /= 10;
	}
	convertedString[i] = '\0';
	return convertedString;
}