#pragma once

#include "Repository.h"

// Return values for functions
#define CONTROLLER_SUCCESS 0
#define CONTROLLER_ERROR -1

typedef struct Controller Controller;

/*
	Constructor for Controller.
	Returns CONTROLLER_SUCCESS in case of a successful allocation - *controller must be
	a valid pointer - CONTROLLER_ERROR otherwise.
*/
int Controller_Create(Controller** controller);

/*
	Destructor for Controller.
	Returns CONTROLLER_SUCCESS in case of a successful deallocation - *controller must be
	a valid pointer - CONTROLLER_ERROR otherwise.
*/
int Controller_Destroy(Controller** controller);

/*
	Initializies a controller object with a repository;
	controller and repository must be valid objects, otherwise CONTROLLER_ERROR is returned.
*/
int Controller_Init(Controller* controller, Repository* repository);

/*
	Adds a bot to the repository. controller and the fields must all be valid.
	Returns CONTROLLER_SUCCESS in case of a successful addition,
	CONTROLLER_ERROR otherwise.
*/
int Controller_AddBot(Controller* controller, int argumentCount, char** argumentVector, int addToStack);

/*
	Updates fields of bot with serial number serialNumber. A bot with serial number serialNumber
	must already exist in the repository (the function
	returns CONTROLLER_ERROR in case the preconditions are not met) CONTROLLER_SUCCESS is returned
	in the case of a successful update.
*/
int Controller_UpdateBot(Controller* controller, int argumentCount, char** argumentVector, int addToStack);

/*
	Deletes bot with the serial number serialNumber from repository.
	If no such bot exists, the function will return CONTROLLER_ERROR, or
	CONTROLLER_SUCCESS otherwise.
*/
int Controller_DeleteBot(Controller* controller, int argumentCount, char** argumentVector, int addToStack);

/*
	Returns bot with serial number serialNumber from repository.
	Returns NULL if the bot does not exist, or the bot otherwise.
*/
Bot* Controller_GetBot(Controller* controller, const char* serialNumber);

/*
	Returns a list of bots that have the same specialization as the given parameter.
	The function takes a filter function and a specialization - the resulted filter size is returned through filterSize.
	If no bots fit the given criteria, the function returns NULL.
*/
Bot** Controller_FilterBotSpecialization(Controller* controller, int* filterSize, const char* specialization, int(*filter)(Bot* bot, const char* specialization));

/*
	Returns a list of bots that have the same specialization as the given parameter.
	The function takes a filter function and a specialization - the resulted filter size is returned through filterSize.
	If no bots fit the given criteria, the function returns NULL.
*/
Bot** Controller_FilterBotCapacity(Controller* controller, int* filterSize, int capacity, int(*filter)(Bot* bot, int capacity));

/*
	Sorts a list of bots with the size listSize by comparisonFunction.
	Returns the same list of bots sorted, or NULL if an error occured.
*/
Bot** Controller_SortBots(Bot** bots, int listSize, int(*comparisonFunction)(Bot* bot1, Bot* bot2));

/*
	Undoes the lastest operation done by the user.
*/
int Controller_Undo(Controller* controller);

/*
	Redoes the lastest operation done by the user.
*/
int Controller_Redo(Controller* controller);