#include "Controller.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONTROLLER_CALL_STACK_CAPACITY 200

#define OPERATION_ADD_ARGUMENT_COUNT 4
#define OPERATION_REMOVE_ARGUMENT_COUNT 4
#define OPERATION_UPDATE_ARGUMENT_COUNT 8
#define OPERATION_DEFAULT_SERIAL_INDEX 0
#define OPERATION_DEFAULT_STATE_INDEX 1
#define OPERATION_DEFAULT_SPECIALIZATION_INDEX 2
#define OPERATION_DEFAULT_CAPACITY_INDEX 3
#define OPERATION_NEW_SERIAL_INDEX 4
#define OPERATION_NEW_STATE_INDEX 5
#define OPERATION_NEW_SPECIALIZATION_INDEX 6
#define OPERATION_NEW_CAPACITY_INDEX 7

struct Controller
{
	Repository* Repository;
};

static int Controller_ValidSerialNumber(const char* serial);

static int Controller_ValidState(const char* state);

static int Controller_ValidSpecialization(const char* spec);

static int Controller_ValidCapacity(float capacity);

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
		printf("Error creating controller!\n");
		return CONTROLLER_ERROR;
	}
	tempController->Repository = NULL;
	tempController->CallStack = NULL;
	tempController->StackSize = -1;
	tempController->StackIndex = -1;
	tempController->StackCapacity = CONTROLLER_CALL_STACK_CAPACITY;
	*controller = tempController;
	return CONTROLLER_SUCCESS;
}

int Controller_Destroy(Controller** controller)
{
	Controller* tempController = *controller;
	if (tempController == NULL)
	{
		printf("Error destroying controller! (Controller was already destroyed)");
		return CONTROLLER_ERROR;
	}
	for (int i = 0; i < tempController->StackSize; i++)
	{
		for (int j = 0; j < tempController->CallStack[i].ArgumentCount; j++)
		{
			free(tempController->CallStack[i].Arguments[j]);
		}
		free(tempController->CallStack[i].Arguments);
	}
	Repository_Destroy(&(tempController->Repository));
	free(tempController->CallStack);
	tempController->StackSize = -1;
	tempController->StackIndex = -1;	
	tempController->StackCapacity = CONTROLLER_CALL_STACK_CAPACITY;
	tempController = NULL;
	controller = NULL;
	return CONTROLLER_SUCCESS;
}

int Controller_Init(Controller* controller, Repository* repository)
{
	if (controller == NULL)
	{
		printf("Invalid controller!\n");
		return CONTROLLER_ERROR;
	}
	if (repository == NULL)
	{
		printf("Invalid Repositorysitory!\n");
		return CONTROLLER_ERROR;
	}
	controller->Repository = repository;
	controller->CallStack = malloc(CONTROLLER_CALL_STACK_CAPACITY * sizeof(Operation));
	return CONTROLLER_SUCCESS;
}

int Controller_AddBot(Controller* controller, const char* serialNumber, const char* state,
					  const char* specialization, int capacity, int addToStack)
{
	if (controller == NULL)
	{
		printf("Invalid controller!\n");
		return CONTROLLER_ERROR;
	}
	if (!Controller_ValidSerialNumber(serialNumber))
	{
		printf("Invalid serial number!\n");
		return CONTROLLER_ERROR;
	}
	if (!Controller_ValidState(state))
	{
		printf("Invalid state!\n");
		return CONTROLLER_ERROR;
	}
	if (!Controller_ValidSpecialization(specialization))
	{
		printf("Invalid specialization!\n");
		return CONTROLLER_ERROR;
	}
	if (!Controller_ValidCapacity(capacity))
	{
		printf("Invalid capacity!\n");
		return CONTROLLER_ERROR;
	}
	Bot* bot = NULL;
	Bot_Create(&bot);
	Bot_Init(bot, state, specialization, serialNumber, capacity);
	Repository_AddBot(controller->Repository, bot);
	if (controller->StackSize == controller->StackCapacity)
	{
		Operation* tempCallStack = malloc(controller->StackCapacity * 2 * sizeof(Operation));
		if (tempCallStack == NULL)
		{
			printf("Error adding bot!\n");
			return CONTROLLER_ERROR;
		}
		controller->StackCapacity *= 2;
		controller->CallStack = tempCallStack;
	}
	if (addToStack)
	{
		char** arguments = malloc(OPERATION_ADD_ARGUMENT_COUNT * sizeof(char*));
		char* stringCapacity = ConvertIntToString(capacity);
		arguments[OPERATION_DEFAULT_SERIAL_INDEX] = malloc(strlen(serialNumber) + 1);
		arguments[OPERATION_DEFAULT_STATE_INDEX] = malloc(strlen(state) + 1);
		arguments[OPERATION_DEFAULT_SPECIALIZATION_INDEX] = malloc(strlen(specialization) + 1);
		arguments[OPERATION_DEFAULT_CAPACITY_INDEX] = malloc(strlen(stringCapacity));
		strcpy(arguments[OPERATION_DEFAULT_SERIAL_INDEX], serialNumber);
		strcpy(arguments[OPERATION_DEFAULT_STATE_INDEX], state);
		strcpy(arguments[OPERATION_DEFAULT_SPECIALIZATION_INDEX], specialization);
		strcpy(arguments[OPERATION_DEFAULT_CAPACITY_INDEX], stringCapacity);
		free(stringCapacity);
		controller->CallStack[controller->StackSize++] = (Operation) { .Type = OPERATION_ADD, .ArgumentCount = 4, .Arguments = arguments };
		controller->StackIndex++;
	}
	return CONTROLLER_SUCCESS;
}

int Controller_UpdateBot(Controller* controller, const char* serialNumber, 
						 const char* newState, const char* newSpecilaization, int newCapacity, int addToStack)
{
	if (controller == NULL)
	{
		printf("Invalid controller!\n");
		return CONTROLLER_ERROR;
	}
	if (!Controller_ValidSerialNumber(serialNumber))
	{
		printf("Invalid serial number!\n");
		return CONTROLLER_ERROR;
	}
	if (!Controller_ValidState(newState))
	{
		printf("Invalid new state!\n");
		return CONTROLLER_ERROR;
	}
	if (!Controller_ValidSpecialization(newSpecilaization))
	{
		printf("Invalid new specialization!\n");
		return CONTROLLER_ERROR;
	}
	if (!Controller_ValidCapacity(newCapacity))
	{
		printf("Invalid new capacity!\n");
		return CONTROLLER_ERROR;
	}
	Repository_UpdateBot(controller->Repository, serialNumber, newState,
						 newSpecilaization, newCapacity);
	return CONTROLLER_SUCCESS;
}

int Controller_DeleteBot(Controller* controller, const char* serialNumber, int addToStack)
{
	if (controller == NULL)
	{
		printf("Invalid controller!\n");
		return CONTROLLER_ERROR;
	}
	if (!Controller_ValidSerialNumber(serialNumber))
	{
		printf("Invalid serial number!\n");
		return CONTROLLER_ERROR;
	}
	if (addToStack)
	{
		Bot* bot = Controller_GetBot(controller, serialNumber);
		if (bot != NULL)
		{
			char* botSerialNumber = Bot_GetSerialNumber(bot);
			char* botState = Bot_GetState(bot);
			char* botSpecialization = Bot_GetSpecialization(bot);
			int botCapacity = Bot_GetCapacity(bot);
			char* stringCapacity = ConvertIntToString(botCapacity);
			char** arguments = malloc(OPERATION_REMOVE_ARGUMENT_COUNT * sizeof(char*));
			arguments[OPERATION_DEFAULT_SERIAL_INDEX] = malloc(strlen(botSerialNumber) + 1);
			arguments[OPERATION_DEFAULT_STATE_INDEX] = malloc(strlen(botState) + 1);
			arguments[OPERATION_DEFAULT_SPECIALIZATION_INDEX] = malloc(strlen(botSpecialization) + 1);
			arguments[OPERATION_DEFAULT_CAPACITY_INDEX] = malloc(strlen(stringCapacity) + 1);
			strcpy(arguments[OPERATION_DEFAULT_SERIAL_INDEX], botSerialNumber);
			strcpy(arguments[OPERATION_DEFAULT_STATE_INDEX], botState);
			strcpy(arguments[OPERATION_DEFAULT_SPECIALIZATION_INDEX], botSpecialization);
			strcpy(arguments[OPERATION_DEFAULT_CAPACITY_INDEX], stringCapacity);
			free(stringCapacity);
		}
	}
	Repository_DeleteBot(controller->Repository, serialNumber);
	return CONTROLLER_SUCCESS;
}

Bot* Controller_GetBot(Controller* controller, const char* serialNumber)
{
	if (controller == NULL)
	{
		printf("Invalid controller!\n");
		return NULL;
	}
	return Repository_GetBot(controller->Repository, serialNumber);
}

Bot** Controller_FilterBots(Controller* controller, int* filterSize, const char* specialization, int(*filter)(Bot* bot, const char* specialization))
{
	if (controller == NULL)
	{
		printf("Invalid controller!\n");
		return NULL;
	}
	return Repository_FilterBots(controller->Repository, filterSize, specialization, filter);
}

Bot** Controller_FilterBotsInt(Controller* controller, int* filterSize, int(*filter)(Bot* bot, int criteria), int criteria)
{
	if (controller == NULL)
	{
		printf("Invalid controller!\n");
		return NULL;
	}
	return Repository_FilterBotsInt(controller->Repository, filterSize, filter, criteria);
}

void Controller_SortBots(Bot** bots, int botCount, int(*filter)(Bot* bot1, Bot* bot2))
{
	Repository_SortBots(bots, botCount, filter);
}

static int Controller_ValidSerialNumber(const char* serial)
{
	return 1;
}

static int Controller_ValidState(const char* state)
{
	return 1;
}

static int Controller_ValidSpecialization(const char* spec)
{
	return 1;
}

static int Controller_ValidCapacity(float capacity)
{
	return 1;
}

