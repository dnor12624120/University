#pragma once

#include "Controller.h"

typedef struct Interface Interface;

/*
	Constructor for Interface.
	Returns INTERFACE_SUCCESS in case of a successful allocation - *interface must be
	a valid pointer - INTERFACE_ERROR otherwise.
*/
int Interface_Create(Interface** interface);

/*
	Destructor for Interface.
	Returns INTERFACE_SUCCESS in case of a successful deallocation - *interface must be
	a valid pointer - INTERFACE_ERROR otherwise.
*/
int Interface_Destroy(Interface** interface);

/*
	Initializies an interface object with a controller;
	controller and repository must be valid objects, otherwise INTERFACE_ERROR is returned.
*/
int Interface_Init(Interface* interface, Controller* controller);

/*
	Starts the main loop of the interface, taking user input, validating it and
	running user commands. Users can quit by typing 'exit'.
*/
void Interface_Run(Interface* interface);

/*
	Gets input from user and parses it into a string array. argumentCount contains the number
	of arguments after parsing, and argumentVector contains the actual arguments.
*/
void Interface_GetInput(Interface* interface, int* argumentCount, char*** argumentVector);

/*
	Resets argumentCount and argumentVector after a loop iteration.
*/
void Interface_ClearInput(int* argumentCount, char** argumentVector);

/*
	Validates user input and returns an function index based on it,
	or INTERFACE_ERROR if the command was not recognized or a wrong number of
	arguments was supplied.
*/
int Interface_ValidateInput(Interface* interface, int argumentCount, char** argumentVector);

/*
	Function for exiting user interface.
*/
void Interface_Exit(Interface* interface, int argumentCount, char** argumentVector);

/*
	Function for adding a bot to the controller.
*/
void Interface_AddBot(Interface* interface, int argumentCount, char** argumentVector);

/*
	Function for updating a bot.
*/
void Interface_UpdateBot(Interface* interface, int argumentCount, char** argumentVector);

/*
	Function for deleting a bot from the controller.
*/
void Interface_DeleteBot(Interface* interface, int argumentCount, char** argumentVector);

/*
	Function for listing all bots.
*/
void Interface_ListBots(Interface* interface, int argumentCount, char** argumentVector);

/*
	Function for listing all bots with a given specialization.
*/
void Interface_ListSpecialization(Interface* interface, int argumentCount, char** argumentVector);
