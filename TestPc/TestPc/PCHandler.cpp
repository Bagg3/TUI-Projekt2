#include "PCHandler.h"
#include <iostream>
#include <vector>
#include <conio.h>
#include <sstream>

#define DATA_LENGTH 255
const char *portName = "\\\\.\\COM3";
SerialPort *arduino;
std::string receivedData;

PCHandler::PCHandler(std::string password)
{
    User admin(password);
    rum = 10;
}

PCHandler::PCHandler(User *admin, SerialPort *arduino)
{
    userPtr = admin;
    this->arduino = arduino;
    rum = 10;
}

void PCHandler::showMenu()
{
    bool running = true;
    while (running)
    {
        int choice = 0;

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
            std::cout << "7. Exit" << std::endl
                      << std::endl;

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
                initialiseSystem();
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
            case 7:
                std::cout << "You chose to exit." << std::endl;
                running = false;
                user.logout();
                break;
            default:
                std::cout << "Invalid choice. Please choose again." << std::endl;
                break;
            }

            std::cout << std::endl;
            if (running)
                clearScreen();
        }
    }
}

void PCHandler::printData()
{
    int choice = 0;
    bool goBack = false;

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
            printLog();
            break;
        case 2:
            std::cout << "You chose to print the raw data" << std::endl;
            printRawData();
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

void PCHandler::changeSystem()
{

    int choice = 0;
    bool goBack = false;

    while (!goBack)
    {
        clearScreen();
        std::cout << "Please choose an option:" << std::endl;
        std::cout << "1. Add a new slave" << std::endl;
        std::cout << "2. Select room connection" << std::endl;
        std::cout << "3. Change amounts of room" << std::endl;
        std::cout << "4. Go Back" << std::endl;

        std::cin >> choice;

        switch (choice)
        {
        case 1:
            addSlave();
            break;
        case 2:
            selectRoomConnection();
            break;
        case 3:
            setRum();
            break;
        case 4:
            goBack = true;
            break;
        default:
            std::cout << "Invalid choice. Please choose again. Press any key to continue" << std::endl;
            _getch();
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

void PCHandler::addSlave()
{
    clearScreen();
    bool validChoice = false;

    std::string slaveAdress;
    int roomNumber;

    while (!validChoice)
    {
        std::cout << "Input the slave address (8-bit binary): " << std::endl;
        std::cin >> slaveAdress;

        if (isValidBinary(slaveAdress))
        {
            std::cout << "You chose to change the slave adress to " << slaveAdress << std::endl;
            validChoice = true;
        }
        else
        {
            std::cout << "Invalid choice. Please choose again." << std::endl;
        }
    }

    validChoice = false;
    while (!validChoice)
    {
        std::cout << std::endl
                  << "Input the room number: " << std::endl;
        std::cin >> roomNumber;
        if (roomNumber >= 0 && roomNumber <= rum)
        {
            std::cout << "You chose to change the number of slaves to " << roomNumber << std::endl;
            validChoice = true;
            break;
        }
        else
        {
            std::cout << "Invalid choice. Please choose again." << std::endl;
        }
    }

    // Convert the slave adress and room number to a string
    slaveAdress += "," + std::to_string(roomNumber);
    std::string slaveAdresstoSend = "B," + slaveAdress;

    std::cout << "Slave adress and room number: " << slaveAdress << std::endl;
    _getch();

    /*
        const char *slaveAdressChar = slaveAdressToSend.c_str();

        // Send the slave adress and room number to the arduino
        arduino->writeSerialPort(slaveAdressChar, DATA_LENGTH);

        */
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
            arduino->~SerialPort();
        }
    }
    */

    std::string string1 = "10 20 40 30 0 0 0 0 0 0";
    std::string string2 = "20 10 30 20 10 0 0 0 0 0";
    std::string string3 = "30 0 20 10 10 10 10 0 0 0";
    std::string string4 = "40 10 20 10 10 0 0 0 0 0";
    std::string string5 = "0 40 10 20 10 10 0 0 0 0";
    std::string string6 = "0 0 40 10 20 10 10 0 0 0";
    std::string string7 = "0 0 0 0 10 20 70 0 0 0";
    std::string string8 = "0 0 0 0 40 10 20 10 10 0";
    std::string string9 = "0 0 0 0 0 40 10 20 10 0";
    std::string string10 = "0 0 40 0 0 0 30 20 10 0";

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

void PCHandler::printLog()
{
    std::vector<std::string> data = getLog();
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
            int l = 1;
            if (arr[k] == highest)
            {
                std::cout << "Person " << l << " "
                          << "Rum " << k + 1 << " er det mest besogte rum" << std::endl;
                l++;
            }
        }
    }

    std::cout << std::endl
              << "Press any key to continue..." << std::endl;
    _getch();
}

void PCHandler::printRawData()
{
    std::vector<std::string> data = getLog();

    for (int i = 0; i < data.size(); i++)
    {
        std::cout << data[i] << std::endl;
    }

    std::cout << std::endl
              << "Press any key to continue..." << std::endl;
    _getch();
}

void PCHandler::setRum()
{
    std::cout << "Enter the number of rooms: " << std::endl;
    std::cin >> rum;
}

void PCHandler::initialiseSystem() const
{
    clearScreen();
    /*
        const char *sendString = "D,1,2,3";

        arduino->isConnected();

        if (arduino->isConnected())
        {
            bool hasWritten = arduino->writeSerialPort(sendString, DATA_LENGTH);
            if (hasWritten)
            {
                std::cout << "Data written successfully." << std::endl;
                Sleep(2000);
            }
        }

        */

    std::cout << "System initialised successfully." << std::endl;
    _getch();
}

bool PCHandler::isValidBinary(const std::string &input)
{
    // Check if the input has exactly 8 characters
    if (input.length() != 8)
        return false;

    // Check if each character is either '0' or '1'
    for (char c : input)
    {
        if (c != '0' && c != '1')
            return false;
    }

    return true;
}

bool PCHandler::isValidRoom(const std::string &input)
{

    std::stringstream ss(input); // Create a stringstream to extract values separated by commas
    std::string segment;         // Store each segment between commas

    while (std::getline(ss, segment, ',')) // Extract segments between commas
    {
        int roomValue;
        try
        {
            roomValue = std::stoi(segment); // Convert the segment to an integer
        }
        catch (const std::invalid_argument &e)
        {
            return false; // The segment couldn't be converted to an integer
        }
        catch (const std::out_of_range &e)
        {
            return false; // The segment is out of the valid range for an integer
        }

        if (roomValue < 1 || roomValue > rum)
            return false; // The room value is outside the valid range
    }

    return true; // All room values are within the valid range
}

void PCHandler::selectRoomConnection()
{
    clearScreen();
    int roomNumber;
    std::cout << "Select room to specify its connections:" << std::endl;
    bool validChoice = false;
    std::string roomConnections;

    while (!validChoice)
    {
        std::cout << std::endl
                  << "Input the room number 1 to " << rum << ": " << std::endl;
        std::cin >> roomNumber;
        if (roomNumber >= 0 && roomNumber <= rum)
        {
            std::cout << "Pick the roomnumbers that room is connected to, sepearte by ONLY ',' " << std::endl;
            std::cin >> roomConnections;

            if (isValidRoom(roomConnections))
            {
                std::cout << "Room " << roomNumber << " is connected to: " << roomConnections << std::endl;
                validChoice = true;
            }
            else
            {
                std::cout << "Invalid input. Please try again." << std::endl;
            }
            validChoice = true;
            break;
        }
        else
        {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    _getch();
}