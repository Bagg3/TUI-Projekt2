// #pragma once
#ifndef DBHANDLER_H
#define DBHANDLER_H
#include <string>

class dbHandler

{

public:
    dbHandler(std::string dbHost = "C:/Users/andre/Documents/GitHub/TUIVSS/TestPc/TestPc/");

    // Decrypts the data from the file and returns it
    std::string findData(const std::string &fileAdress, bool decrypt); // Uses try catch syntax

    // Encrypts the data and saves it to the file
    void saveData(std::string fileAdress, std::string data, bool encrypt); // Uses try catch syntax

    void setSaveOnline(bool save);

    bool getSaveOnline();

private:
    std::string dbHost = "C:/Users/andre/Documents/GitHub/TUIVSS/TestPc/TestPc/";
    std::string dbHostOnline = "C:/Users/andre/OneDrive/Universitet/2 Semester/Projekt2";

    // Function to encrypt/decrypt the data
    std::string xorCipher(std::string data, char key);

    void saveCipheredDataToFile(const std::string &fileAdress, const std::string &data, char key);
    char loadKeyFromFile();
    bool saveOnline;

    std::string laptop = "C:/Users/andre/Documents/GitHub/TUIVSS/TestPc/TestPc/";
};

#endif