#include "Interface.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Return values for functions
#define INTERFACE_SUCCESS 0
#define INTERFACE_ERROR -1

// Size for function pointer array
#define MENU_LIST_SIZE 9

// Size for input buffer
#define MAX_BUFFER_SIZE 4096

// Indices for menu function parameters
#define ADD_BOT_SERIAL_INDEX 1
#define ADD_BOT_STATE_INDEX 2
#define ADD_BOT_SPECIALIZATION_INDEX 3
#define ADD_BOT_CAPACITY_INDEX 4
#define REMOVE_BOT_SERIAL_INDEX 1
#define UPDATE_BOT_SERIAL_INDEX 1
#define UPDATE_BOT_NEW_STATE_INDEX 2
#define UPDATE_BOT_NEW_SPECIALIZATION_INDEX 3
#define UPDATE_BOT_NEW_CAPACITY_INDEX 4
#define LIST_SPECIALIZATION_INDEX 1
#define LIST_CAPACITY_INDEX 1

// Argument counts for functions
#define EXIT_ARGUMENT_COUNT 0
#define ADD_BOT_ARGUMENT_COUNT 4
#define UPDATE_BOT_ARGUMENT_COUNT 4
#define REMOVE_BOT_ARGUMENT_COUNT 1
#define LIST_ALL_ARGUMENT_COUNT 0
#define LIST_SPECIALIZATION_ARGUMENT_COUNT 1
#define LIST_CAPACITY_ARGUMENT_COUNT 1
#define UNDO_ARGUMENT_COUNT 0
#define REDO_ARGUMENT_COUNT 0

// Indices for menu/command list arrays
#define MENU_EXIT 0
#define MENU_ADD_BOT 1
#define MENU_UPDATE_BOT 2
#define MENU_REMOVE_BOT 3
#define MENU_LIST_ALL 4
#define MENU_LIST_SPECIALIZATION 5
#define MENU_LIST_CAPACITY 6
#define MENU_UNDO 7
#define MENU_REDO 8

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

/*
	Function for checking if a string is numerical.
*/
static int IsStringNumerical(const char* string);

/*
	Function for converting a given string to an integer.
*/
static int ConvertStringToInt(const char* string);

/*
	Function for printing formatted bot information.
*/
static void Interface_PrintBot(Bot* bot, int index);

/*
	Returns all bots from controller.
*/
static int Interface_GetAll(Bot* bot, const char* specialization);

/*
	Checks if the supplied bot has specialization as its specialization.
*/
static int Interface_FilterSpecialization(Bot* bot, const char* specialization);

/*
	Checks if the supplied bot's capacity is less than the given one.
*/
static int Interface_FilterCapacity(Bot* bot, int capacity);

/*
	Alphabetically compares the states of the 2 bots provided.
*/
static int Interface_CompareStates(Bot* bot1, Bot* bot2);

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
	interface->Menus[MENU_EXIT] = Interface_Exit;
	interface->Menus[MENU_ADD_BOT] = Interface_AddBot;
	interface->Menus[MENU_UPDATE_BOT] = Interface_UpdateBot;
	interface->Menus[MENU_REMOVE_BOT] = Interface_DeleteBot;
	interface->Menus[MENU_LIST_ALL] = Interface_ListBots;
	interface->Menus[MENU_LIST_SPECIALIZATION] = Interface_ListSpecialization;
	interface->Menus[MENU_LIST_CAPACITY] = Interface_ListCapacity;
	interface->Menus[MENU_UNDO] = Interface_Undo;
	interface->Menus[MENU_REDO] = Interface_Redo;
	interface->Commands[MENU_EXIT] = (Command) { .ArgumentCount = EXIT_ARGUMENT_COUNT, .Name = "exit" };
	interface->Commands[MENU_ADD_BOT] = (Command) { .ArgumentCount = ADD_BOT_ARGUMENT_COUNT, .Name = "add" };
	interface->Commands[MENU_UPDATE_BOT] = (Command) { .ArgumentCount = UPDATE_BOT_ARGUMENT_COUNT, .Name = "update" };
	interface->Commands[MENU_REMOVE_BOT] = (Command) { .ArgumentCount = REMOVE_BOT_ARGUMENT_COUNT, .Name = "delete" };
	interface->Commands[MENU_LIST_ALL] = (Command) { .ArgumentCount = LIST_ALL_ARGUMENT_COUNT, .Name = "list" };
	interface->Commands[MENU_LIST_SPECIALIZATION] = (Command) { .ArgumentCount = LIST_SPECIALIZATION_ARGUMENT_COUNT, .Name = "list" };
	interface->Commands[MENU_LIST_CAPACITY] = (Command) { .ArgumentCount = LIST_CAPACITY_ARGUMENT_COUNT, .Name = "list" };
	interface->Commands[MENU_UNDO] = (Command) { .ArgumentCount = UNDO_ARGUMENT_COUNT, .Name = "undo" };
	interface->Commands[MENU_REDO] = (Command) { .ArgumentCount = REDO_ARGUMENT_COUNT, .Name = "redo" };
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
	// string that input is being read into
	char inputBuffer[MAX_BUFFER_SIZE];
	int counter = 0; // variable for parsing input and copying arguments separately into argumentVector
	// read input until newline
	scanf("%[^\n]s", inputBuffer);
	// clear buffer in case some weird C input thing happens
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}
	// parse input
	for (int i = 0; inputBuffer[i]; i++)
	{
		if (inputBuffer[i] == ' ')
		{
			(*argumentCount)++; // get argument count
		}
	}
	(*argumentCount)++;
	*argumentVector = malloc(*argumentCount * sizeof(char*)); // allocates space for arugments
	char* argument = NULL;
	// split input into separate arguments
	argument = strtok(inputBuffer, ", ");
	while (argument != NULL)
	{
		(*argumentVector)[counter++] = argument;
		argument = strtok(NULL, ", ");
	}
}

void Interface_ClearInput(int* argumentCount, char** argumentVector)
{
	free(argumentVector);
	*argumentCount = 0;
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
			if (IsStringNumerical(argumentVector[1]))
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
		if(argumentCount != 1)
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
	if (Controller_AddBot(interface->Controller, argumentCount, argumentVector, 1) == CONTROLLER_SUCCESS)
	{
		printf("Bot added successfully!\n");
	}
}

void Interface_UpdateBot(Interface* interface, int argumentCount, char** argumentVector)
{
	if (Controller_UpdateBot(interface->Controller, argumentCount, argumentVector, 1) == CONTROLLER_SUCCESS)
	{
		printf("Bot updated successfully!\n");
	}
}

void Interface_DeleteBot(Interface* interface, int argumentCount, char** argumentVector)
{
	if (Controller_DeleteBot(interface->Controller, argumentCount, argumentVector, 1) == CONTROLLER_SUCCESS)
	{
		printf("Bot deleted successfully!\n");
	}
}

void Interface_ListBots(Interface* interface, int argumentCount, char** argumentVector)
{
	int filterSize = 0;
	Bot** filteredBots = Controller_FilterBotSpecialization(interface->Controller, &filterSize, "", Interface_GetAll);
	for (int i = 0; i < filterSize; i++)
	{
		Interface_PrintBot(filteredBots[i], i + 1);
	}
	free(filteredBots);
}

void Interface_ListSpecialization(Interface* interface, int argumentCount, char** argumentVector)
{
	int filterSize = 0;
	Bot** filteredBots = Controller_FilterBotSpecialization(interface->Controller, &filterSize, argumentVector[1], Interface_FilterSpecialization);
	for (int i = 0; i < filterSize; i++)
	{
		Interface_PrintBot(filteredBots[i], i + 1);
	}
	free(filteredBots);
}

void Interface_ListCapacity(Interface* interface, int argumentCount, char** argumentVector)
{
	int filterSize = 0;
	Bot** filteredBots = Controller_FilterBotCapacity(interface->Controller, &filterSize, ConvertStringToInt(argumentVector[1]),
													  Interface_FilterCapacity);
	filteredBots = Controller_SortBots(filteredBots, filterSize, Interface_CompareStates);
	for (int i = 0; i < filterSize; i++)
	{
		Interface_PrintBot(filteredBots[i], i + 1);
	}
	free(filteredBots);
}

void Interface_Undo(Interface* interface, int argumentCount, char** argumentVector)
{
	if (interface == NULL)
	{
		return INTERFACE_ERROR;
	}
	if (Controller_Undo(interface->Controller) == CONTROLLER_ERROR)
	{
		printf("No more operations to undo!\n");
		return INTERFACE_ERROR;
	}
	return INTERFACE_SUCCESS;
}

void Interface_Redo(Interface* interface, int argumentCount, char** argumentVector)
{
	if (interface == NULL)
	{
		return INTERFACE_ERROR;
	}
	if (Controller_Redo(interface->Controller) == CONTROLLER_ERROR)
	{
		printf("No more operations to redo!\n");
		return INTERFACE_ERROR;
	}
	return INTERFACE_SUCCESS;
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

static int Interface_FilterCapacity(Bot* bot, int capacity)
{
	int botCapacity = Bot_GetCapacity(bot);
	return botCapacity < capacity;
}

static int IsStringNumerical(const char* string)
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

static int Interface_CompareStates(Bot* bot1, Bot* bot2)
{
	char* state1 = Bot_GetState(bot1);
	char* state2 = Bot_GetState(bot2);
	return strcmp(state1, state2) > 0;
}