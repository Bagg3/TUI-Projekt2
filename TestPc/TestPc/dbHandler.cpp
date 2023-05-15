#include "dbHandler.h"
#include <string>
#include <iostream>
#include <fstream>

// Constructor with default dbHost - folder name of the database
dbHandler::dbHandler(std::string dbHost)
{
    dbHost_ = dbHost;
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
std::string dbHandler::findData(std::string fileAdress)
{
    // Tries to open file, if it fails, throws an error
    std::string data;
    std::ifstream file;
    file.open(dbHost_ + fileAdress);
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

    char key;
    // Load key from key file
    std::ifstream keyFile;
    keyFile.open(dbHost_ + "key.txt");
    if (keyFile.is_open())
    {
        std::string line;
        getline(keyFile, line);
        key = line[0];
        keyFile.close();
    }
    else
    {
        throw std::runtime_error("Unable to open file");
    }
    // Returns the deciphered data
    return xorCipher(data, key);
}

// Encrypt data to file, using key from key.txt, where fileAdress is the name of the file in UserDB folder
void dbHandler::saveData(std::string fileAdress, std::string data)
{
    // Load key from key file
    char key;
    std::ifstream keyFile;
    keyFile.open(dbHost_ + "key.txt");
    if (keyFile.is_open())
    {
        std::string line;
        getline(keyFile, line);
        key = line[0];
        keyFile.close();
    }
    else
    {
        throw std::runtime_error("Unable to open file");
    }
    // Saves the ciphered data to file
    std::ofstream file;
    file.open(dbHost_ + fileAdress);
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
