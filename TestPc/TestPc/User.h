// #pragma once
#ifndef USER_H
#define USER_H

#include <string>
#include "dbHandler.h"
#include <windows.h>

class User
{
private:
	// Variables
	std::string password_;
	bool isLoggedIn_;
	dbHandler db;

public:
	User();
	User(dbHandler dataBase, std::string password = "admin");

	// Function to login to the system, checks if the username and password are correct, Return if the login is true og not
	void login();

	// Function to logout of the system
	void logout();

	// Function to check if the user is logged in
	bool isLoggedIn();

	// Function to change the password of the user, username
	void changePassword();

	// Function to clear the terminal
	void clearScreen();

	int getWindowWidth();
	void setConsoleColor(WORD attributes);
	void printHorizontalLine(int width, WORD attributes);
	void printCenteredText(const std::string &text, int padding, WORD attributes);
};

#endif