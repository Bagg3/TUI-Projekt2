#include "dbHandler.h"
#include <string>
#include <iostream>
#include <fstream>

std::string dbHandler::xorCipher(std::string data, char key)
{
    std::string result = data;
    for (int i = 0; i < data.size(); i++)
    {
        result[i] = data[i] ^ key;
    }
    return result;
}

dbHandler::dbHandler(std::string dbHost)
{
    dbHost_ = dbHost;
}

std::string dbHandler::findData(std::string fileAdress)
{
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

    return xorCipher(data, key);
}

void dbHandler::saveData(std::string fileAdress, std::string data)
{
    std::ofstream file;
    file.open(dbHost_ + fileAdress);
    if (file.is_open())
    {
        file << data;
        file.close();
    }
    else
    {
        throw std::runtime_error("Unable to open file");
    }
}
