#include <iostream>
#include <string>
#include "User.h"
#include "PCHandler.h"

#define portName "\\\\.\\COM3"

int main()
{
	// Setting up objects and dependcies
	dbHandler db;
	User admin(db);
	SerialPort arduino(portName);

	PCHandler PC(&admin, &arduino, &db);
	admin.clearScreen();
	PC.showMenu();

	return 0;
}

/*
# include<windows.h>
HANDLE console = GetStdHandle(STD_INPUT_HANDLE);
DWORD consoleMode;
GetConsoleMode(console, &consoleMode);

//Remove echo from console
SetConsoleMode(console, consoleMode & ~ENABLE_ECHO_INPUT);

// Set console to default
SetConsoleMode(console, consoleMode);
*/
