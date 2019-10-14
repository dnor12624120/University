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

#define BOT_BUFFER_SIZE 1024

struct Bot
{
	char State[BOT_BUFFER_SIZE];
	char Specialization[BOT_BUFFER_SIZE];
	char SerialNumber[BOT_BUFFER_SIZE];
	int Capacity;
};

int Bot_Create(Bot** bot)
{
	Bot* tempBot = (Bot*)malloc(sizeof(Bot));
	if (tempBot == NULL) // return an error in case malloc failed
	{
		return BOT_ERROR;
	}
	// initialize fields with default values
	tempBot->Capacity = 0;
	*bot = tempBot;
	return BOT_SUCCESS;
}

int Bot_Destroy(Bot** bot)
{
	Bot* temp = *bot;
	if (*bot == NULL) // check if bot was already destructed 
	{
		return BOT_ERROR;
	}
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
		return BOT_ERROR;
	}
	// Initialize serial number
	strcpy_s(bot->SerialNumber, BOT_BUFFER_SIZE, serialNumber);
	// Initialize state
	strcpy_s(bot->State, BOT_BUFFER_SIZE, state);
	// Initialize specialization
	strcpy_s(bot->Specialization, BOT_BUFFER_SIZE, specialization);
	// Initialize capacity
	bot->Capacity = capacity;
	return BOT_SUCCESS;
}

int Bot_Update(Bot* bot, const char* newState,
			   const char* newSpecialization, int newCapacity)
{
	if (bot == NULL)
	{
		return BOT_ERROR;
	}
	// Update state
	strcpy_s(bot->State, BOT_BUFFER_SIZE, newState);
	// Update specialization
	strcpy_s(bot->Specialization, BOT_BUFFER_SIZE, newSpecialization);
	// Update capacity
	bot->Capacity = newCapacity;
	return BOT_SUCCESS;
}

const char* Bot_GetState(Bot* bot)
{
	if (bot == NULL) // Check if bot is valid
	{
		return NULL;
	}
	return bot->State;
}

const char* Bot_GetSpecialization(Bot* bot)
{
	if (bot == NULL) // Check if bot is valid
	{
		return NULL;
	}
	return bot->Specialization;
}

char const* Bot_GetSerialNumber(Bot* bot)
{
	if (bot == NULL) // Check if bot is valid
	{
		return NULL;
	}
	return bot->SerialNumber;
}

int Bot_GetCapacity(Bot* bot)
{
	if (bot == NULL) // Check if bot is valid
	{
		return BOT_ERROR;
	}
	return bot->Capacity;
}

