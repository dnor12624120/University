#pragma once

//Return values for functions
#define BOT_ERROR -1
#define BOT_SUCCESS 0

typedef struct Bot Bot;

/*
	Constructor for Bot.
	Returns Bot_SUCCESS in case of a successful allocation - *bot must be
	a valid pointer - Bot_ERROR otherwise.
*/
int Bot_Create(Bot** bot);

/*
	Destructor for Bot.
	Returns Bot_SUCCESS in case of a successful deallocation - *bot must be
	a valid pointer - Bot_ERROR otherwise.
*/
int Bot_Destroy(Bot** bot);

/*
	Initializes a bot with given values.
	Returns Bot_SUCCESS in case of a successful initialization - bot must be
	a valid pointer - Bot_ERROR otherwise.
*/
int Bot_Init(Bot* bot, const char* state, const char* specialization, const char* serial, int capacity);

/*
	Updates the fields of a bot.
	Returns Bot_SUCCESS in case of a successful update - bot must be
	a valid pointer - Bot_ERROR otherwise.
*/
int Bot_Update(Bot* bot, const char* newState,
			   const char* newSpecialization, int newCapacity);

/*
	Returns the state of a bot - NULL in case bot is not valid, or its state otherwise.
*/
const char* Bot_GetState(Bot* bot);

/*
	Returns the specialization of a bot - NULL in case bot is not valid,
	or its specialization otherwise.
*/
const char* Bot_GetSpecialization(Bot* bot);

/*
	Returns the serial number of a bot - NULL in case bot is not valid,
	or a string of its serial number otherwise.
*/
char const* Bot_GetSerialNumber(Bot* bot);

/*
	Returns the energy capacity of a bot - -1 in case bot is not valid,
	or its capacity otherwise.
*/
int Bot_GetCapacity(Bot* bot);

