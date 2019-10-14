#include "Bot.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FUNCTIONAL_STATE "functional"
#define IMPAIRED_STATE "impaired"
#define FAULTY_STATE "faulty"

#define MAINTENANCE_SPECIALIZATION "maintenance"
#define PATROL_SPECIALIZATION "patrol"
#define MEDICAL_SPECIALIZATION "medical"

struct Bot
{
	char* State;
	char* Specialization;
	char* SerialNumber;
	int Capacity;
};

int Bot_Create(Bot** bot)
{
	Bot* tempBot = (Bot*)malloc(sizeof(Bot));
	if (tempBot == NULL) // return an error in case malloc failed
	{
		printf("Error creating Bot!\n");
		return BOT_ERROR;
	}
	// initialize fields with default values
	tempBot->State = NULL;
	tempBot->Specialization = NULL;
	tempBot->SerialNumber = NULL;
	tempBot->Capacity = 0;
	*bot = tempBot;
	return BOT_SUCCESS;
}

int Bot_Destroy(Bot** bot)
{
	Bot* temp = *bot;
	if (*bot == NULL) // check if bot was already destructed 
	{
		printf("Error destroying Bot! (Bot was already destroyed)\n");
		return BOT_ERROR;
	}
	// free dynamically allocated fields
	free(temp->State);
	free(temp->Specialization);
	free(temp->SerialNumber);
	// set them to their default values
	temp->State = NULL;
	temp->Specialization = NULL;
	temp->SerialNumber = NULL;
	temp->Capacity = 0;
	free(temp);
	// make bot invalid
	temp = NULL;
	// make pointer to bot invalid
	bot = NULL;
	return BOT_SUCCESS;
}

int Bot_Init(Bot* bot, const char* state, const char* specialization, const char* serialNumber, int capacity)
{
	if (bot == NULL) // check if bot is valid
	{
		printf("Invalid bot!\n");
		return BOT_ERROR;
	}
	// Initialize serial number
	bot->SerialNumber = malloc(sizeof(char) * (strlen(serialNumber) + 1));
	if (bot->SerialNumber == NULL)
	{
		printf("Error allocating space for bot serial number!\n");
		return BOT_ERROR;
	}
	strcpy(bot->SerialNumber, serialNumber);
	// Initialize state
	bot->State = malloc(sizeof(char) * (strlen(state) + 1));
	if (bot->State == NULL)
	{
		printf("Error allocating space for bot state!\n");
		return BOT_ERROR;
	}
	strcpy(bot->State, state);
	// Initialize specialization
	bot->Specialization = malloc(sizeof(char) * (strlen(specialization) + 1));
	if (bot->Specialization == NULL)
	{
		printf("Error allocating space for bot specialization!\n");
		return BOT_ERROR;
	}
	strcpy(bot->Specialization, specialization);
	// Initialize capacity
	bot->Capacity = capacity;
	return BOT_SUCCESS;
}

int Bot_Update(Bot* bot, const char* newState,
			   const char* newSpecialization, int newCapacity)
{
	if (bot == NULL)
	{
		printf("Invalid bot!\n");
		return BOT_ERROR;
	}
	// Update state
	free(bot->State);
	bot->State = malloc(sizeof(char) * (strlen(newState) + 1));
	if (bot->State == NULL)
	{
		printf("Error allocating space for bot state!\n");
		return BOT_ERROR;
	}
	strcpy(bot->State, newState);
	// Update specialization
	free(bot->Specialization);
	bot->Specialization = malloc(sizeof(char) * strlen((newSpecialization)+1));
	if (bot->Specialization == NULL)
	{
		printf("Error allocating space for bot specialization!\n");
		return BOT_ERROR;
	}
	strcpy(bot->Specialization, newSpecialization);
	// Update capacity
	bot->Capacity = newCapacity;
	return BOT_SUCCESS;
}

const char* Bot_GetState(Bot* bot)
{
	if (bot == NULL) // Check if bot is valid
	{
		printf("Invalid bot!\n");
		return NULL;
	}
	return bot->State;
}

const char* Bot_GetSpecialization(Bot* bot)
{
	if (bot == NULL) // Check if bot is valid
	{
		printf("Invalid bot!\n");
		return NULL;
	}
	return bot->Specialization;
}

char const* Bot_GetSerialNumber(Bot* bot)
{
	if (bot == NULL) // Check if bot is valid
	{
		printf("Invalid bot!\n");
		return NULL;
	}
	return bot->SerialNumber;
}

int Bot_GetCapacity(Bot* bot)
{
	if (bot == NULL) // Check if bot is valid
	{
		printf("Invalid bot!\n");
		return -1;
	}
	return bot->Capacity;
}

