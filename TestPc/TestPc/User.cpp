#include "User.h"
#include <string>
#include <iostream>
#include <fstream>
#include <functional>
#include <Windows.h>

User::User()
{
	dbHandler db;
	password_ = "admin";
	isLoggedIn_ = false;
}

User::User(dbHandler dataBase, std::string password)
{
	// Checks if password is empty, if it is, then it will set the password to admin
	db = dataBase;
	if (db.findData("db.txt", true) == "")
	{
		db.saveData("db.txt", password, true);
	}
	password_ = db.findData("db.txt", true);
	isLoggedIn_ = false;
}

void User::validate(std::string password)
{

	if (password == password_)
	{
		std::cout << "Login successful" << std::endl;
		isLoggedIn_ = true;
	}
	else
	{
		std::cout << "Login failed try again" << std::endl;
	}
}

void User::login()
{
	// Checks if the user is logged in, if not, then it will ask for a password adn check if it is correct
	while (!isLoggedIn())
	{
		clearScreen();
		std::string password;
		std::cout << "Login to the system" << std::endl;
		std::cout << "Password: ";
		std::cin >> password;
		validate(password);
		/*
				// Used to bypass the database
				if (password == "admin")
				{
					isLoggedIn_ = true;
					return;
				}

				*/
	}
}

/*
void User::login()
{
	// Checks if the user is logged in, if not, then it will ask for a password
	while (!isLoggedIn())
	{
		clearScreen();
		std::string password;
		std::cout << "Login to the system" << std::endl;
		std::cout << "Password: ";
		std::cin >> password;

		// Used to bypass the database
		if (password == "admin")
		{
			isLoggedIn_ = true;
			return;
		}
	}
}
*/
void User::logout()
{
	isLoggedIn_ = false;
}

bool User::isLoggedIn()
{
	return isLoggedIn_;
}

void User::changePassword()
{
	// Saves the new password to the database
	clearScreen();
	std::string newPassword;
	std::cout << "Enter new password: ";
	std::cin >> newPassword;
	password_ = newPassword;
	db.saveData("db.txt", newPassword, true);
}

int User::getWindowWidth()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	return width;
}

void User::setConsoleColor(WORD attributes)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, attributes);
}

void User::printHorizontalLine(int width, WORD attributes)
{
	setConsoleColor(attributes);
	for (int i = 0; i < width; i++)
	{
		std::cout << " ";
	}
	setConsoleColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	std::cout << std::endl;
}

void User::printCenteredText(const std::string &text, int padding, WORD attributes)
{
	setConsoleColor(attributes);
	for (int i = 0; i < padding; i++)
	{
		std::cout << " ";
	}

	std::cout << text;

	int remainingWidth = getWindowWidth() - padding - text.length();
	for (int i = 0; i < remainingWidth; i++)
	{
		std::cout << " ";
	}
	setConsoleColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void User::clearScreen()
{
	int consoleWidth = getWindowWidth();
	std::string text = "Intelligent Pattern Recognition System";
	int padding = (consoleWidth - static_cast<int>(text.length())) / 2;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	WORD savedAttributes = csbi.wAttributes; // Save current console attributes

	system("cls");

	printHorizontalLine(consoleWidth, BACKGROUND_INTENSITY | BACKGROUND_BLUE /*| BACKGROUND_GREEN | BACKGROUND_RED*/);
	printCenteredText(text, padding, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);

	std::cout << std::endl;
	printHorizontalLine(consoleWidth, BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);

	SetConsoleTextAttribute(hConsole, savedAttributes); // Restore original console attributes
	/*
		system("cls");														// Code to clear the screen
		std::cout << "Intelligent Pattern Recognition System" << std::endl;
		*/
	// "IPRS SYSTEM
	std::cout << std::endl
			  << std::endl;
}