#include "User.h"
#include <string>
#include <iostream>
#include <fstream>
#include <functional>


User::User()
{
	dbHandler db;
	password_ = "admin";
	isLoggedIn_ = false;
}

User::User(dbHandler dataBase, std::string password)
{

	db = dataBase;
	if (db.findData("db.txt", true) == "")
	{
		db.saveData("db.txt", password, true);
	}
	password_ = db.findData("db.txt", true);
	isLoggedIn_ = false;
}

void User::clearScreen() const
{
	system("cls");                                                      // Code to clear the screen
	std::cout << "Intelligent Pattern Recognition System" << std::endl; // "IPRS SYSTEM
	std::cout << std::endl
		<< std::endl;
}

void User::login()
{

	while (!isLoggedIn())
	{
		clearScreen();
		std::string password;
		std::cout << "Login to the system" << std::endl;
		std::cout << "Password: ";
		std::cin >> password;

		if (password == password_)
		{
			std::cout << "Login successful" << std::endl;
			isLoggedIn_ = true;
		}
		else
		{
			std::cout << "Login failed try again" << std::endl;
		}
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
	std::string newPassword;
	std::cout << "Enter new password: ";
	std::cin >> newPassword;
	password_ = newPassword;
	dbHandler db("../UserDB/");
	db.saveData("db.txt", newPassword, true);
}