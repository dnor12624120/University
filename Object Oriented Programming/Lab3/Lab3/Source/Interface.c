#include "Interface.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INTERFACE_SUCCESS 0
#define INTERFACE_ERROR -1
#define MENU_LIST_SIZE 6
#define MAX_BUFFER_SIZE 4096

typedef struct Command
{
	int ArgumentCount;
	char* Name;
} Command;

struct Interface
{
	Controller* Controller;
	void (*Menus[MENU_LIST_SIZE])(Interface* interface, int argumentCount, char** argumentVector);
	Command Commands[MENU_LIST_SIZE];
	int Running;
};

static int ConvertStringToInt(const char* string)
{
	int convertedNumber = 0;
	for (int i = 0; string[i]; i++)
	{
		convertedNumber = convertedNumber * 10 + string[i] - '0';
	}
	return convertedNumber;
}

static int IsStringNumeric(const char* string)
{
	for (int i = 0; string[i]; i++)
	{
		if (!isdigit(string[i]))
		{
			return 0;
		}
	}
	return 1;
}

static void Interface_PrintBot(Bot* bot, int index)
{
	const char* serialNumber = Bot_GetSerialNumber(bot);
	const char* state = Bot_GetState(bot);
	const char* specialization = Bot_GetSpecialization(bot);
	int capacity = Bot_GetCapacity(bot);

	printf("Robot #%d:\n", index);
	printf("Serial number: %s\n", serialNumber);
	printf("State: %s\n", state);
	printf("Specialization: %s\n", specialization);
	printf("Energy capacity: %d\n", capacity);
}

static int Interface_GetAll(Bot* bot, const char* specialization)
{
	return 1;
}

static int Interface_FilterSpecialization(Bot* bot, const char* specialization)
{
	char* botSpecialization = Bot_GetSpecialization(bot);
	return strcmp(specialization, botSpecialization) == 0;
}

int Interface_Create(Interface** interface)
{
	Interface* tempInterface = malloc(sizeof(Interface));
	if (tempInterface == NULL)
	{
		printf("Error creating interface!\n");
		return INTERFACE_ERROR;
	}
	tempInterface->Controller = NULL;
	tempInterface->Running = 0;
	*interface = tempInterface;
	return INTERFACE_SUCCESS;
}

int Interface_Destroy(Interface** interface)
{
	Interface* tempInterface = *interface;
	if (tempInterface == NULL)
	{
		printf("Error destroying interface! (Interface was already destroyed)");
		return INTERFACE_ERROR;
	}
	Controller_Destroy(&(tempInterface->Controller));
	memset(tempInterface->Menus, 0, sizeof(tempInterface->Menus));
	memset(tempInterface->Commands, 0, sizeof(tempInterface->Commands));
	tempInterface->Running = 0;
	tempInterface = NULL;
	interface = NULL;
	return INTERFACE_SUCCESS;
}

int Interface_Init(Interface* interface, Controller* controller)
{
	if (interface == NULL)
	{
		printf("Invalid interface!\n");
		return INTERFACE_ERROR;
	}
	if (controller == NULL)
	{
		printf("Invalid controller!\n");
		return INTERFACE_ERROR;
	}
	interface->Controller = controller;
	interface->Menus[0] = Interface_Exit;
	interface->Menus[1] = Interface_AddBot;
	interface->Menus[2] = Interface_UpdateBot;
	interface->Menus[3] = Interface_DeleteBot;
	interface->Menus[4] = Interface_ListBots;
	interface->Menus[5] = Interface_ListSpecialization;
	interface->Commands[0] = (Command) { .ArgumentCount = 0, .Name = "exit" };
	interface->Commands[1] = (Command) { .ArgumentCount = 4, .Name = "add" };
	interface->Commands[2] = (Command) { .ArgumentCount = 4, .Name = "update" };
	interface->Commands[3] = (Command) { .ArgumentCount = 1, .Name = "delete" };
	interface->Commands[4] = (Command) { .ArgumentCount = 0, .Name = "list" };
	interface->Commands[5] = (Command) { .ArgumentCount = 1, .Name = "list" };
	interface->Running = 1;
	return INTERFACE_SUCCESS;
}

void Interface_Run(Interface* interface)
{
	int argumentCount = 0;
	char** argumentVector = NULL;
	while (interface->Running)
	{
		Interface_GetInput(interface, &argumentCount, &argumentVector);
		int index = Interface_ValidateInput(interface, argumentCount, argumentVector);
		if (index != INTERFACE_ERROR)
		{
			interface->Menus[index](interface, argumentCount, argumentVector);
		}
		Interface_ClearInput(&argumentCount, argumentVector);
	}
}

void Interface_GetInput(Interface* interface, int* argumentCount, char*** argumentVector)
{	
	char inputBuffer[MAX_BUFFER_SIZE];
	int i = 0;
	scanf("%[^\n]s", inputBuffer);
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}
	for (int i = 0; inputBuffer[i]; i++)
	{
		if (inputBuffer[i] == ' ')
		{
			(*argumentCount)++;
		}
	}
	(*argumentCount)++;
	*argumentVector = malloc(*argumentCount * sizeof(char*));
	char* argument = NULL;
	argument = strtok(inputBuffer, ", ");
	while (argument != NULL)
	{
		(*argumentVector)[i++] = argument;
		argument = strtok(NULL, ", ");
	}
}

void Interface_ClearInput(int* argumentCount, char** argumentVector)
{
	*argumentCount = 0;
	free(argumentVector);
}

int Interface_ValidateInput(Interface* interface, int argumentCount, char** argumentVector)
{
	if (strcmp(argumentVector[0], "exit") == 0)
	{
		if (argumentCount != 1)
		{
			printf("Invalid number of arguments!\n");
			return INTERFACE_ERROR;
		}
		return 0;
	}
	else if (strcmp(argumentVector[0], "add") == 0)
	{
		if (argumentCount != 5)
		{
			printf("Invalid number of arguments!\n");
			return INTERFACE_ERROR;
		}
		return 1;
	}
	else if (strcmp(argumentVector[0], "update") == 0)
	{
		if (argumentCount != 5)
		{
			printf("Invalid number of arguments!\n");
			return INTERFACE_ERROR;
		}
		return 2;
	}
	else if (strcmp(argumentVector[0], "delete") == 0)
	{
		if (argumentCount != 2)
		{
			printf("Invalid number of arguments!\n");
			return INTERFACE_ERROR;
		}
		return 3;
	}
	else if (strcmp(argumentVector[0], "list") == 0)
	{
		if (argumentCount == 1)
		{
			return 4;
		}
		else if(argumentCount == 2)
		{
			if (IsStringNumeric(argumentVector[1]))
			{
				return 6;
			}
			return 5;
		}
		else
		{
			if (argumentCount != 1)
			{
				printf("Invalid number of arguments!\n");
				return INTERFACE_ERROR;
			}
		}
	}
	else if (strcmp(argumentVector[0], "undo") == 0)
	{
		if (argumentCount != 1)
		{
			printf("Invalid number of arguments!\n");
			return INTERFACE_ERROR;
		}
		return 7;
	}
	else if (strcmp(argumentVector[0], "redo") == 0)
	{
		if (argumentCount != 1)
		{
			printf("Invalid number of arguments!\n");
			return INTERFACE_ERROR;
		}
		return 8;
	}
	else
	{
		printf("Invalid command!\n");
		return INTERFACE_ERROR;
	}
}

void Interface_Exit(Interface* interface, int argumentCount, char** argumentVector)
{
	interface->Running = 0;
}

void Interface_AddBot(Interface* interface, int argumentCount, char** argumentVector)
{
	if (Controller_AddBot(interface->Controller, argumentVector[1], argumentVector[2], argumentVector[3], ConvertStringToInt(argumentVector[4]), 1) == CONTROLLER_SUCCESS)
	{

	}
}

void Interface_UpdateBot(Interface* interface, int argumentCount, char** argumentVector)
{
	if (Controller_UpdateBot(interface->Controller, argumentVector[1], argumentVector[2], argumentVector[3], ConvertStringToInt(argumentVector[4]), 1) == CONTROLLER_SUCCESS)
	{

	}
}

void Interface_DeleteBot(Interface* interface, int argumentCount, char** argumentVector)
{
	if (Controller_DeleteBot(interface->Controller, argumentVector[1], 1) == CONTROLLER_SUCCESS)
	{

	}
}

void Interface_ListBots(Interface* interface, int argumentCount, char** argumentVector)
{
	int filterSize = 0;
	Bot** filteredBots = Controller_FilterBots(interface->Controller, &filterSize, "", Interface_GetAll);
	for (int i = 0; i < filterSize; i++)
	{
		Interface_PrintBot(filteredBots[i], i + 1);
	}
	free(filteredBots);
}

void Interface_ListSpecialization(Interface* interface, int argumentCount, char** argumentVector)
{
	int filterSize = 0;
	Bot** filteredBots = Controller_FilterBots(interface->Controller, &filterSize, argumentVector[1], Interface_FilterSpecialization);
	for (int i = 0; i < filterSize; i++)
	{
		Interface_PrintBot(filteredBots[i], i + 1);
	}
	free(filteredBots);
}
