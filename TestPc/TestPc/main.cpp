#include <iostream>
#include <string>
#include "User.h"
#include "PCHandler.h"

int main()
{
	// User user("admin");
	//  SerialPort arduino(portName);

	PCHandler PC("admin");
	PC.clearScreen();
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
