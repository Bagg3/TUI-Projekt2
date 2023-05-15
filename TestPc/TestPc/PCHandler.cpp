#include "PCHandler.h"
#include <iostream>
#include <vector>
#include <conio.h>

#define DATA_LENGTH 255
const char *portName = "\\\\.\\COM3";
SerialPort *arduino;
std::string receivedData;

PCHandler::PCHandler(std::string password)
{
    User admin(password);
}

PCHandler::PCHandler(User *admin, SerialPort *arduino)
{
    userPtr = admin;
    this->arduino = arduino;
}

void PCHandler::showMenu()
{
    while (true)
    {
        int choice = 0;
        // bool isLoggedIn = true;

        user.login();

        while (user.isLoggedIn())
        {
            clearScreen();
            std::cout << "Please choose an option:" << std::endl;
            std::cout << "1. Print Data" << std::endl;
            std::cout << "2. Make Change To System" << std::endl;
            std::cout << "3. Initialise System" << std::endl;
            std::cout << "4. Change The Log" << std::endl;
            std::cout << "5. Change Password" << std::endl;
            std::cout << "6. Log out" << std::endl;

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
                std::cout << "You chose to initialise the system." << std::endl;
                // Code to calibrate the system
                break;
            case 4:
                // Code to change the log
                break;
            case 5:
                std::cout << "You chose to change the password." << std::endl;
                user.changePassword();
                break;
            case 6:
                std::cout << "You chose to log out." << std::endl;
                user.logout();
                break;
            default:
                std::cout << "Invalid choice. Please choose again." << std::endl;
                break;
            }

            std::cout << std::endl;
            clearScreen();
        }
    }
}

void PCHandler::printData()
{
    int choice = 0;
    bool goBack = false;

    std::vector<std::string> Log;

    while (!goBack)
    {
        clearScreen();
        std::cout << "Please choose an option:" << std::endl;
        std::cout << "1. Print Formatet Log" << std::endl;
        std::cout << "2. Print Raw Data" << std::endl;
        std::cout << "3. Go Back" << std::endl;

        std::cin >> choice;

        switch (choice)
        {
        case 1:
            std::cout << "You chose to print the formated log." << std::endl;
            Log = getLog();
            printLog(Log);
            break;
        case 2:
            std::cout << "You chose to print the raw data" << std::endl;
            Log = getLog();
            printRawData(Log);
            break;
        case 3:
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

    int choice = 0;
    bool goBack = false;

    while (!goBack)
    {
        clearScreen();
        std::cout << "Please choose an option:" << std::endl;
        std::cout << "1. Add a new slave" << std::endl;
        std::cout << "2. Select room connection" << std::endl;
        std::cout << "3. Go Back" << std::endl;

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
    system("cls");                           // Code to clear the screen
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

std::vector<std::string> PCHandler::getLog()
{
    std::vector<std::string> data;

    /*
    arduino = new SerialPort(portName);
    arduino->isConnected();
    std::cout << "Is connected: " << arduino->isConnected() << std::endl;

    while (arduino->isConnected())
    {
        char receivedChar;
        int hasRead = arduino->readSerialPort(&receivedChar, 1);
        if (hasRead)
        {
            if (receivedChar != '\n')
            {
                receivedData += receivedChar;
            }
            else
            {
                data.push_back(receivedData);
                receivedData.clear();
            }
        }
        if (data.size() == 10)
        {
            break;
        }
    }
    */

    std::string string1 = "10 20 40 30 0 0 0 0 0 0";
    std::string string2 = "20 10 30 20 10 0 0 0 0 0";
    std::string string3 = "30 0 20 10 10 10 10 0 0 0";
    std::string string4 = "40 10 20 10 10 0 0 0 0 0";
    std::string string5 = "0 40 10 20 10 10 0 0 0 0";
    std::string string6 = "0 0 40 10 20 10 10 0 0 0";
    std::string string7 = "0 0 0 0 10 30 70 0 0 0";
    std::string string8 = "0 0 0 0 40 10 20 10 10 0";
    std::string string9 = "0 0 0 0 0 40 10 20 10 0";
    std::string string10 = "0 0 0 0 0 0 30 30 10 0";

    data.push_back(string1);
    data.push_back(string2);
    data.push_back(string3);
    data.push_back(string4);
    data.push_back(string5);
    data.push_back(string6);
    data.push_back(string7);
    data.push_back(string8);
    data.push_back(string9);
    data.push_back(string10);

    return data;
}

void PCHandler::printLog(std::vector<std::string> data)
{
    for (int j = 0; j < data.size(); j++)
    {

        data[j].push_back(' ');
        int rum = 10;

        // Function to convert exempel to int array, split on " "
        std::string delimiter = " ";
        size_t pos = 0;
        std::string token;
        int i = 0;
        int arr[10];
        while ((pos = data[j].find(delimiter)) != std::string::npos)
        {
            token = data[j].substr(0, pos);
            // std::cout << token << std::endl;
            arr[i] = std::stoi(token);
            data[j].erase(0, pos + delimiter.length());
            i++;
        }
        // std::cout << arr << std::endl;

        // function to loop through array and find the highest value
        int highest = 0;
        for (int i = 0; i < rum; i++)
        {
            if (arr[i] > highest)
            {
                highest = arr[i];
            }
        }

        int TOTAL[10];
        TOTAL[j] = highest;

        for (int k = 0; k < rum; k++)
        {
            if (arr[k] == highest)
            {
                std::cout << "Person " << i << " "
                          << "Rum " << k + 1 << " er det mest besogte rum" << std::endl;
            }
        }
    }
    std::cout << std::endl
              << "Press any key to continue..." << std::endl;
    _getch();
}

void PCHandler::printRawData(std::vector<std::string> data)
{

    for (int i = 0; i < data.size(); i++)
    {
        std::cout << data[i] << std::endl;
    }

    std::cout << std::endl
              << "Press any key to continue..." << std::endl;
    _getch();
}
