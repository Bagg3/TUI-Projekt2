#include "User.h"
#include <string>
#include <iostream>
#include <fstream>
#include <functional>

User::User(std::string password)
{
	password_ = password;
	isLoggedIn_ = false;
}

void User::login()
{

	while (!isLoggedIn())
	{
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
	}

}

void User::logout()
{
}

bool User::isLoggedIn()
{
	return isLoggedIn_;
}

void User::changePassword(std::string newPassword)
{
	password_ = newPassword;
}