#include "PCHandler.h"
#include <iostream>
#include <memory.h>

PCHandler::PCHandler(std::string password)
{
	User admin(password);
}

/*
PCHandler::PCHandler(User *user_)
{
	user = user_;
}
*/

void PCHandler::showMenu()
{
	int choice = 0;
	// bool isLoggedIn = true;

	user.login();

	while (user.isLoggedIn())
	{
		clearScreen();
		std::cout << "Welcome to your program!" << std::endl;
		std::cout << "Please choose an option:" << std::endl;
		std::cout << "1. Print Data" << std::endl;
		std::cout << "2. Make change to system" << std::endl;
		std::cout << "3. Calibrate system" << std::endl;
		std::cout << "4. Change Password" << std::endl;
		std::cout << "5. Log out" << std::endl;

		std::cin >> choice;

		switch (choice)
		{
		case 1:
			std::cout << "You chose to print data." << std::endl;
			printData();
			break;
		case 2:
			std::cout << "You chose to make a change to the system." << std::endl;
			changeSystem();
			break;
		case 3:
			std::cout << "You chose to calibrate the system." << std::endl;
			// Code to calibrate the system
			break;
		case 4:
			std::cout << "You chose to change the password." << std::endl;
			user.changePassword("admin");
			break;
		case 5:
			std::cout << "You chose to log out." << std::endl;
			user.logout();
			break;
		default:
			std::cout << "Invalid choice. Please choose again." << std::endl;
			break;
		}

		std::cout << std::endl;
	}
}

void PCHandler::printData()
{
	std::cout << "Printing data..." << std::endl;

	int choice = 0;
	bool goBack = false;

	while (!goBack)
	{
		clearScreen();
		std::cout << "Please choose an option:" << std::endl;
		std::cout << "1. Print Newest Data" << std::endl;
		std::cout << "2. Print Oldest Log" << std::endl;
		std::cout << "3. Print Nothing" << std::endl;
		std::cout << "4. Go Back" << std::endl;

		std::cin >> choice;

		switch (choice)
		{
		case 1:
			std::cout << "You chose to print Newest Data." << std::endl;
			// Code to print data
			break;

		case 2:
			std::cout << "You chose to Print Oldest Log" << std::endl;
			// Code to make a change to the system
			break;
		case 3:
			std::cout << "You chose to Print Nothing." << std::endl;
			// Code to calibrate the system
			break;
		case 4:
			std::cout << "You chose to Go Back." << std::endl;
			goBack = true;
			break;
		default:
			std::cout << "Invalid choice. Please choose again." << std::endl;
			break;
		}

		std::cout << std::endl;
	}
}

void PCHandler::changeSystem() const
{
	std::cout << "Printing data..." << std::endl;

	int choice = 0;
	bool goBack = false;

	while (!goBack)
	{
		clearScreen();
		std::cout << "Welcome to your program!" << std::endl;
		std::cout << "Please choose an option:" << std::endl;
		std::cout << "1. Change Number of slaves" << std::endl;
		std::cout << "2. Print Oldest Log" << std::endl;
		std::cout << "3. Print Nothing" << std::endl;
		std::cout << "4. Go Back" << std::endl;

		std::cin >> choice;

		switch (choice)
		{
		case 1:
			std::cout << "How many slaves?" << std::endl;
			changeSlaves();
			// Code to print data
			break;
		case 2:
			std::cout << "You chose to Print Oldest Log" << std::endl;
			// Code to make a change to the system
			break;
		case 3:
			std::cout << "You chose to Print Nothing." << std::endl;
			// Code to calibrate the system
			break;
		case 4:
			std::cout << "You chose to Go Back." << std::endl;
			goBack = true;
			break;
		default:
			std::cout << "Invalid choice. Please choose again." << std::endl;
			break;
		}

		std::cout << std::endl;
	}
}

void PCHandler::clearScreen() const
{
	system("clear");                         // Code to clear the screen
	std::cout << "IPRS SYSTEM" << std::endl; // "IPRS SYSTEM
	std::cout << std::endl
		<< std::endl;
}

void PCHandler::changeSlaves() const
{
	bool validChoice = false;

	while (!validChoice)
	{
		int Slavechoice;
		std::cin >> Slavechoice;
		if (Slavechoice > 0)
		{
			std::cout << "You chose to change the number of slaves to " << Slavechoice << std::endl;
			validChoice = true;
			break;
		}
		else
		{
			std::cout << "Invalid choice. Please choose again." << std::endl;
		}
	}
}

void printLog()
{
	/*

	string Log = UART.getLockFromArduino();
	Log.Format("Log: %s", Log);
	cout << Log << endl;

	*/
}
