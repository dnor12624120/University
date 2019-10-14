#include "Bot.h"
#include "Repository.h"
#include "Controller.h"
#include "Interface.h"

#include <stdio.h>

int main(int argc, char** argv)
{
	Interface* interface;
	Controller* controller;
	Repository* repository;

	Repository_Create(&repository);

	Controller_Create(&controller);
	Controller_Init(controller, repository);

	Interface_Create(&interface);
	Interface_Init(interface, controller);

	Interface_Run(interface);

	Interface_Destroy(&interface);
	return 0;
}