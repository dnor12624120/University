#pragma once

#include "Bot.h"

// Return values for functions
#define REPOSITORY_SUCCESS 0
#define REPOSITORY_ERROR -1

typedef struct Repository Repository;

/*
	Constructor for Repository.
	Returns REPOSITORY_SUCCESS in case of a successful allocation - *repository must be
	a valid pointer - REPOSTITORY_ERROR otherwise.
*/
int Repository_Create(Repository** repository);

/*
	Destructor for Repository.
	Returns REPOSITORY_SUCCESS in case of a successful deallocation - *repoistory must be
	a valid pointer - REPOSITORY_ERROR otherwise.
*/
int Repository_Destroy(Repository** repository);

/*
	Adds a bot to local array of elements. repository and bot must both
	be valid objects. Returns REPOSITORY_SUCCESS in case of a successful addition,
	REPOSITORY_ERROR otherwise.
*/
int Repository_AddBot(Repository* repository, Bot* bot);

/*
	Updates fields of bot with serial number serialNumber. A bot with serial number serialNumber
	must already exist in the repository, while no bot with newSerialNumber can exist (the function
	returns REPOSITORY_ERROR in case the preconditions are not met) REPOSITORY_SUCCESS is returned
	in the case of a successful update.
*/
int Repository_UpdateBot(Repository* repository, const char* serialNumber,
						 const char* newState, const char* newSpecialization, int newCapacity);

/*
	Deletes bot with the serial number serialNumber from repository.
	If no such bot exists, the function will return REPOSITORY_ERROR, or
	REPOSITORY_SUCCESS otherwise.
*/
int Repository_DeleteBot(Repository* repository, const char* serialNumber);

/*
	Returns the number of bots within the repository, or REPOSITORY_ERROR if
	repository is invalid.
*/
int Repository_GetSize(Repository* repository);

/*
	Returns a pointer to a bot with the serial number serialNumber.
	If no such bot exists or repository is invalid, the function returns NULL.
*/
Bot* Repository_GetBot(Repository* repository, const char* seriaNumber);

/*
	Returns a list of bots that have the same specialization as the given parameter.
	The function takes a filter function and a specialization - the resulted filter size is returned through filterSize.
	If no bots fit the given criteria, the function returns NULL.
*/
Bot** Repository_FilterBotSpecialization(Repository* repository, int* filterSize, const char* specialization, int(*filter)(Bot* bot, const char* specialization));

/*
	Returns a list of bots that have their capacity under the given capacity.
	The function takes a filter function and a capacity - the resulted filter size is returned through filterSize.
	If no bots fit the given criteria, the function returns NULL.
*/
Bot** Repository_FilterBotCapacity(Repository* repository, int* filterSize, int capacity, int(*filter)(Bot* bot, int capacity));

/*
	Sorts a list of bots of size listSize by comparisonFunction.
	Returns the same list of sorted bots, or NULL if an error occured.
*/
Bot** Repository_SortBots(Bot** bots, int listSize, int(*comparisonFunction)(Bot* bot1, Bot* bot2));
