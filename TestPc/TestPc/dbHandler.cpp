#include "dbHandler.h"
#include <string>
#include <iostream>
#include <fstream>

// Constructor with default dbHost - folder name of the database
dbHandler::dbHandler(std::string dbHost)
{
	dbHost = dbHost;
	if (findData("saveSettings.txt", false) == "true")
	{
		bool saveOnline = true;
	}
	else
	{
		bool saveOnline = false;
	}
}

// Function to cipher/decipher data with XOR cipher
std::string dbHandler::xorCipher(std::string data, char key)
{
	std::string result = data;
	for (int i = 0; i < data.size(); i++)
	{
		result[i] = data[i] ^ key;
	}
	return result;
}

// Decrypt data from file, using key from key.txt, where fileAdress is the name of the file in UserDB folder
std::string dbHandler::findData(const std::string &fileAdress, bool decrypt)
{
	std::string data;
	std::ifstream file;
	file.open(dbHost + fileAdress);
	if (file.is_open())
	{
		std::string line;
		while (getline(file, line))
		{
			data += line;
		}
		file.close();
	}
	else
	{
		std::cout << "Unable to open file";
	}

	if (!decrypt)
	{
		return data;
	}

	char key = loadKeyFromFile();

	return xorCipher(data, key);
}

// Encrypt data to file, using key from key.txt, where fileAdress is the name of the file in UserDB folder
void dbHandler::saveData(std::string fileAdress, std::string data, bool encrypt)
{

	if (!encrypt)
	{
		std::ofstream file1(dbHost + fileAdress);
		if (file1.is_open())
		{
			file1 << data;
			file1.close();
		}
		else
		{
			throw std::runtime_error("Unable to open file");
		}

		if (saveOnline)
		{
			std::ofstream file2(dbHostOnline + fileAdress);
			if (file2.is_open())
			{
				file2 << data;
				file2.close();
			}
			else
			{
				throw std::runtime_error("Unable to open file");
			}
		}
		return;
	}

	// Load key from key file
	char key = loadKeyFromFile();
	// Saves the ciphered data to file

	saveCipheredDataToFile(fileAdress, data, key);
}

char dbHandler::loadKeyFromFile()
{
	std::ifstream keyFile(dbHost + "key.txt");
	if (keyFile.is_open())
	{
		std::string line;
		getline(keyFile, line);
		keyFile.close();
		return line[0];
	}
	else
	{
		throw std::runtime_error("Unable to open file");
	}
}

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

void dbHandler::saveCipheredDataToFile(const std::string &fileAdress, const std::string &data, char key)
{
	std::ofstream file(dbHost + fileAdress);
	if (file.is_open())
	{
		file << xorCipher(data, key);
		file.close();
	}
	else
	{
		throw std::runtime_error("Unable to open file");
	}
}

void dbHandler::setSaveOnline(bool save)
{
	saveOnline = save;
	if (saveOnline)
		saveData("saveSettings.txt", "true", false);

	else
		saveData("saveSettings.txt", "false", false);
}

bool dbHandler::getSaveOnline()
{
	return saveOnline;
}