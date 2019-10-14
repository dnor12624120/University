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

static int Repository_FindBot(Repository* repository, const char* serialNumber);
static int SwapBots(Bot** bot1, Bot** bot2);

int Repository_Create(Repository** repository)
{
	Repository* tempRepository = malloc(sizeof(Repository));
	if (tempRepository == NULL)
	{
		printf("Error creating repository!\n");
		return REPOSITORY_ERROR;
	}
	tempRepository->Size = 0;
	tempRepository->Capacity = REPOSITORY_DEFAULT_CAPACITY;
	tempRepository->Elements = malloc(tempRepository->Capacity * sizeof(Bot*));
	if (tempRepository->Elements == NULL)
	{
		printf("Error creating repository!\n");
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
		printf("Error destroying repository! (Repository was already destroyed)\n");
		return REPOSITORY_ERROR;
	}
	for (int i = 0; i < tempRepository->Size; i++)
	{
		Bot_Destroy(&(tempRepository->Elements[i]));
	}
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
		printf("Invalid repo!\n");
		return REPOSITORY_ERROR;
	}
	if (bot == NULL)
	{
		printf("Invalid bot!\n");
		return REPOSITORY_ERROR;
	}
	if (repository->Size == repository->Capacity)
	{
		Bot** tempElements = realloc(repository->Elements, repository->Capacity * 2 * sizeof(Bot*));
		if (tempElements == NULL)
		{
			printf("Error adding bot!\n");
			return REPOSITORY_ERROR;
		}
		repository->Capacity *= 2;
		repository->Elements = tempElements;
	}
	if (Repository_FindBot(repository, Bot_GetSerialNumber(bot)) != REPOSITORY_ERROR)
	{
		printf("Bot serial number is not unique!\n");
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
		printf("Invalid repo!\n");
		return REPOSITORY_ERROR;
	}
	if (serialNumber == NULL)
	{
		printf("Empty serial number!\n");
		return REPOSITORY_ERROR;
	}
	if (newState == NULL)
	{
		printf("Empty serial number!\n");
		return REPOSITORY_ERROR;
	}
	if (newSpecialization == NULL)
	{
		printf("Empty serial number!\n");
		return REPOSITORY_ERROR;
	}
	int botIndex = Repository_FindBot(repository, serialNumber);
	if (botIndex == REPOSITORY_ERROR)
	{
		printf("No bot with given ID exists!\n");
		return REPOSITORY_ERROR;
	}
	Bot_Update(repository->Elements[botIndex], newState, newSpecialization, newCapacity);
	return REPOSITORY_SUCCESS;
}

int Repository_DeleteBot(Repository* repository, const char* serialNumber)
{
	if (repository == NULL)
	{
		printf("Invalid repo!\n");
		return REPOSITORY_ERROR;
	}
	if (serialNumber == NULL)
	{
		printf("Empty serial number!\n");
		return REPOSITORY_ERROR;
	}
	int botIndex = Repository_FindBot(repository, serialNumber);
	if (botIndex == REPOSITORY_ERROR)
	{
		printf("No bot with given ID exists!\n");
		return REPOSITORY_ERROR;
	}
	Bot_Destroy(&(repository->Elements[botIndex]));
	for (int i = botIndex; i < repository->Size - 1 && repository->Size - 1; i++)
	{
		repository->Elements[i] = repository->Elements[i + 1];
	}
	repository->Size--;
	if (repository->Size <= repository->Capacity / 4 && repository->Size > 200)
	{
		Bot** tempElements = realloc(repository->Elements, (repository->Capacity / 2) * sizeof(Bot*));
		if (tempElements == NULL)
		{
			printf("Error removing bot!\n");
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
		printf("Invalid repo!\n");
		return REPOSITORY_ERROR;
	}
	return repository->Size;
}

Bot* Repository_GetBot(Repository* repository, const char* serialNumber)
{
	if (repository == NULL)
	{
		printf("Invalid repo!\n");
		return NULL;
	}
	if (serialNumber == NULL)
	{
		printf("Empty serial number!\n");
		return NULL;
	}
	int botIndex = Repository_FindBot(repository, serialNumber);
	if (botIndex == REPOSITORY_ERROR)
	{
		printf("No bot with given ID exists!\n");
		return NULL;
	}
	return repository->Elements[botIndex];
}

Bot** Repository_FilterBots(Repository* repository, int* filterSize, const char* specialization, int(*filter)(Bot* bot, const char* specialization))
{
	if (repository == NULL)
	{
		printf("Invalid repo!\n");
		return NULL;
	}
	*filterSize = 0;
	for (int i = 0; i < repository->Size; i++)
	{
		if (filter(repository->Elements[i], specialization))
		{
			(*filterSize)++;
		}
	}
	Bot** filteredBots = NULL;
	filteredBots = malloc((*filterSize) * sizeof(Bot*));
	for (int i = 0, j = 0; i < repository->Size; i++)
	{
		if (filter(repository->Elements[i], specialization))
		{
			filteredBots[j++] = repository->Elements[i];
		}
	}
	return filteredBots;
}

Bot** Repository_FilterBotsInt(Repository* repository, int* filterSize, int(*filter)(Bot* bot, int criteria), int criteria)
{
	if (repository == NULL)
	{
		printf("Invalid repo!\n");
		return NULL;
	}
	*filterSize = 0;
	for (int i = 0; i < repository->Size; i++)
	{
		if (filter(repository->Elements[i], criteria))
		{
			(*filterSize)++;
		}
	}
	Bot** filteredBots = NULL;
	filteredBots = malloc((*filterSize) * sizeof(Bot*));
	for (int i = 0, j = 0; i < repository->Size; i++)
	{
		if (filter(repository->Elements[i], criteria))
		{
			filteredBots[j++] = repository->Elements[i];
		}
	}
	return filteredBots;
}


void Repository_SortBots(Bot** bots, int botCount, int(*filter)(Bot* bot1, Bot* bot2))
{
	if (bots == NULL)
	{
		printf("Invalid list of bots!\n");
		return NULL;
	}
	for (int i = 0; i < botCount; i++)
	{
		for (int j = i + 1; j < botCount; j++)
		{
			if (filter(bots[i], bots[j]))
			{
				SwapBots(&(bots[i]), &(bots[j]));
			}
		}
	}
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

static int SwapBots(Bot** bot1, Bot** bot2)
{
	Bot* tempBot = *bot1;
	*bot1 = *bot2;
	*bot2 = tempBot;
}