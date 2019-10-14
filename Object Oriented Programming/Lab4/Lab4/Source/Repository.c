#include "Repository.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REPOSITORY_DEFAULT_CAPACITY 4

struct Repository
{
	Bot** Elements;
	unsigned int Size;
	unsigned int Capacity;
};

/*
	Repository-only function for checking if a bot exists within the repository.
	It returns the index of the bot if it can be found, or -1 otherwise.
*/
static int Repository_FindBot(Repository* repository, const char* serialNumber);

/*
	Auxiliary swap function for interchaning 2 bots when sorting a list of bots.
*/
static void Swap(Bot** bot1, Bot** bot2);

int Repository_Create(Repository** repository)
{
	Repository* tempRepository = malloc(sizeof(Repository));
	if (tempRepository == NULL)
	{
		return REPOSITORY_ERROR;
	}
	// set fields to default values
	tempRepository->Size = 0;
	tempRepository->Capacity = REPOSITORY_DEFAULT_CAPACITY;
	tempRepository->Elements = malloc(tempRepository->Capacity * sizeof(Bot*));
	if (tempRepository->Elements == NULL)
	{
		return REPOSITORY_ERROR;
	}
	*repository = tempRepository;
	return REPOSITORY_SUCCESS;
}

int Repository_Destroy(Repository** repository)
{
	Repository* tempRepository = *repository;
	if (tempRepository == NULL)
	{
		return REPOSITORY_ERROR;
	}
	// destroy bots first
	for (int i = 0; i < tempRepository->Size; i++)
	{
		Bot_Destroy(&(tempRepository->Elements[i]));
	}
	// reset fields to default values
	tempRepository->Size = 0;
	tempRepository->Capacity = REPOSITORY_DEFAULT_CAPACITY;
	free(tempRepository->Elements);
	free(tempRepository);
	tempRepository = NULL;
	repository = NULL;
	return REPOSITORY_SUCCESS;
}

int Repository_AddBot(Repository* repository, Bot* bot)
{
	if (repository == NULL)
	{
		return REPOSITORY_ERROR;
	}
	if (bot == NULL)
	{
		return REPOSITORY_ERROR;
	}
	if (repository->Size == repository->Capacity)
	{
		// if the repository is at max capacity, double its capacity
		Bot** tempElements = realloc(repository->Elements, repository->Capacity * 2 * sizeof(Bot*));
		if (tempElements == NULL)
		{
			return REPOSITORY_ERROR;
		}
		repository->Capacity *= 2;
		repository->Elements = tempElements;
	}
	if (Repository_FindBot(repository, Bot_GetSerialNumber(bot)) != REPOSITORY_ERROR)
	{
		//return an error if a bot with the given serial number already exists
		return REPOSITORY_ERROR;
	}
	repository->Elements[repository->Size++] = bot;
	return REPOSITORY_SUCCESS;
}

int Repository_UpdateBot(Repository* repository, const char* serialNumber, 
						 const char* newState, const char* newSpecialization, int newCapacity)
{
	if (repository == NULL)
	{
		return REPOSITORY_ERROR;
	}
	// validate new bot fields
	if (serialNumber == NULL)
	{
		return REPOSITORY_ERROR;
	}
	if (newState == NULL)
	{
		return REPOSITORY_ERROR;
	}
	if (newSpecialization == NULL)
	{
		return REPOSITORY_ERROR;
	}
	int botIndex = Repository_FindBot(repository, serialNumber);
	if (botIndex == REPOSITORY_ERROR)
	{
		// return an error if such a bot doesn't exist within the repository
		return REPOSITORY_ERROR;
	}
	Bot_Update(repository->Elements[botIndex], newState, newSpecialization, newCapacity);
	return REPOSITORY_SUCCESS;
}

int Repository_DeleteBot(Repository* repository, const char* serialNumber)
{
	if (repository == NULL)
	{
		return REPOSITORY_ERROR;
	}
	if (serialNumber == NULL)
	{
		return REPOSITORY_ERROR;
	}
	int botIndex = Repository_FindBot(repository, serialNumber);
	if (botIndex == REPOSITORY_ERROR)
	{
		// return an error if no such bot exists within the repository
		return REPOSITORY_ERROR;
	}
	// destroy the bot
	Bot_Destroy(&(repository->Elements[botIndex]));
	// move bots back to fill the empty spot in the repository array
	for (int i = botIndex; i < repository->Size - 1 && repository->Size - 1; i++)
	{
		repository->Elements[i] = repository->Elements[i + 1];
	}
	repository->Size--;
	// downsize the repository if the size is way less than the capacity
	if (repository->Size <= repository->Capacity / 4)
	{
		Bot** tempElements = realloc(repository->Elements, (repository->Capacity / 2) * sizeof(Bot*));
		if (tempElements == NULL)
		{
			return REPOSITORY_ERROR;
		}
		repository->Capacity /= 2;
		repository->Elements = tempElements;
	}
	return REPOSITORY_SUCCESS;
}

int Repository_GetSize(Repository* repository)
{
	if (repository == NULL)
	{
		return REPOSITORY_ERROR;
	}
	return repository->Size;
}

Bot* Repository_GetBot(Repository* repository, const char* serialNumber)
{
	if (repository == NULL)
	{
		return NULL;
	}
	if (serialNumber == NULL)
	{
		return NULL;
	}
	int botIndex = Repository_FindBot(repository, serialNumber);
	if (botIndex == REPOSITORY_ERROR)
	{
		return NULL;
	}
	return repository->Elements[botIndex];
}

Bot** Repository_FilterBotSpecialization(Repository* repository, int* filterSize, const char* specialization, int(*filter)(Bot* bot, const char* specialization))
{
	if (repository == NULL)
	{
		return NULL;
	}
	*filterSize = 0;
	// check how many bots have the given specialization
	for (int i = 0; i < repository->Size; i++)
	{
		if (filter(repository->Elements[i], specialization))
		{
			(*filterSize)++;
		}
	}
	// allocate space for that many bots
	Bot** filteredBots = NULL;
	filteredBots = malloc((*filterSize) * sizeof(Bot*));
	// save the bots to the array
	for (int i = 0, j = 0; i < repository->Size; i++)
	{
		if (filter(repository->Elements[i], specialization))
		{
			filteredBots[j++] = repository->Elements[i];
		}
	}
	return filteredBots;
}

Bot** Repository_FilterBotCapacity(Repository* repository, int* filterSize, int capacity, int(*filter)(Bot* bot, int capacity))
{
	if (repository == NULL)
	{
		return NULL;
	}
	*filterSize = 0;
	// check how many bots have the given specialization
	for (int i = 0; i < repository->Size; i++)
	{
		if (filter(repository->Elements[i], capacity))
		{
			(*filterSize)++;
		}
	}
	// allocate space for that many bots
	Bot** filteredBots = NULL;
	filteredBots = malloc((*filterSize) * sizeof(Bot*));
	// save the bots to the array
	for (int i = 0, j = 0; i < repository->Size; i++)
	{
		if (filter(repository->Elements[i], capacity))
		{
			filteredBots[j++] = repository->Elements[i];
		}
	}
	return filteredBots;
}

Bot** Repository_SortBots(Bot** bots, int listSize, int(*comparisonFunction)(Bot* bot1, Bot* bot2))
{
	for (int i = 0; i < listSize; i++)
	{
		for (int j = i + 1; j < listSize; j++)
		{
			if (comparisonFunction(bots[i], bots[j]))
			{
				Swap(&(bots[i]), &(bots[j]));
			}
		}
	}
	return bots;
}

static int Repository_FindBot(Repository* repository,  const char* serialNumber)
{
	for (unsigned int i = 0; i < repository->Size; i++)
	{
		if (strcmp(Bot_GetSerialNumber(repository->Elements[i]), serialNumber) == 0)
		{
			return i;
		}
	}
	return REPOSITORY_ERROR;
}

static void Swap(Bot** bot1, Bot** bot2)
{
	Bot* tempBot = *bot1;
	*bot1 = *bot2;
	*bot2 = tempBot;
}