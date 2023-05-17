// #pragma once
#ifndef DBHANDLER_H
#define DBHANDLER_H
#include <string>

class dbHandler

{
private:
	std::string dbHost_;

	// Function to encrypt/decrypt the data
	std::string xorCipher(std::string data, char key);

public:
	dbHandler(std::string dbHost = "C:/Users/andre/Documents/GitHub/TUIVSS/TestPc/TestPc/");
	// C:/Users/andre/Documents/GitHub/TUIVSS/TestPc/TestPc/

	// Decrypts the data from the file and returns it
	std::string findData(std::string fileAdress, bool decrypt); // Uses try catch syntax

	// Encrypts the data and saves it to the file
	void saveData(std::string fileAdress, std::string data, bool encrypt); // Uses try catch syntax
};

#endif