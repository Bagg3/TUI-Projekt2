#include "PCHandler.h"
#include <iostream>
#include <vector>
#include <conio.h>
#include <sstream>
#include <fstream>

#define DATA_LENGTH 255
// const char* portName = "\\\\.\\COM3";
SerialPort *arduino;
std::string receivedData;

PCHandler::PCHandler(std::string password)
{
    User admin(password);
    amountOfRooms = 10;
    amountOfUsers = 10;
}

PCHandler::PCHandler(User *admin, SerialPort *arduino)
{
    userPtr = admin;
    this->arduino = arduino;
    amountOfRooms = 10;
    amountOfUsers = 10;
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
            // Print the menu
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
                printData();
                break;
            case 2:
                changeSystem();
                break;
            case 3:
                initialiseSystem();
                break;
            case 4:
                changeLog();
                break;
            case 5:
                user.changePassword();
                // userPtr->changePassword();
                break;
            case 6:
                user.logout();
                break;
            case 7:;
                running = false;
                user.logout();
                break;
            default:
                std::cout << "Invalid choice. Please choose again." << std::endl;
                break;
            }

            // Only clears the screen if program is running
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
    std::vector<int> log;

    while (!goBack)
    {
        clearScreen();
        // The various print options
        std::cout << "Please choose an option:" << std::endl;
        std::cout << "1. Print Formatet Log" << std::endl;
        std::cout << "2. Print Raw Data" << std::endl;
        std::cout << "3. Go Back" << std::endl
                  << std::endl;

        std::cin >> choice;

        switch (choice)
        {
        case 1:
            log = formatLog();
            printLog(log);
            nextMenu();
            break;
        case 2:
            printRawData();
            break;
        case 3:
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
        // The various change system options
        std::cout << "Please choose an option:" << std::endl;
        std::cout << "1. Add a new slave" << std::endl;
        std::cout << "2. Select room connection" << std::endl;
        std::cout << "3. Change amounts of rooms" << std::endl;
        std::cout << "4. Change amounts of users" << std::endl;
        std::cout << "5. Go Back" << std::endl;

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
            setRooms();
            break;
        case 4:
            setUsers();
            break;
        case 5:
            goBack = true;
            break;
        default:
            std::cout << "Invalid choice. Please choose again. Press any key to continue" << std::endl;
            break;
        }

        std::cout << std::endl;
    }
}

void PCHandler::addSlave()
{
    clearScreen();

    // Instantiate of variables
    bool validChoice = false;
    int slaveAdress;
    int roomNumber;

    // Makes sure the user inputs a valid binary number
    while (!validChoice)
    {
        std::cout << "Input the slave address in a valid whole number in the interval 1-255: " << std::endl;
        std::cin >> slaveAdress;

        if (slaveAdress >= 1 && slaveAdress <= 255)
        {
            std::cout << "You chose to change the slave adress to " << slaveAdress << std::endl;
            validChoice = true;
        }
        else
        {
            std::cout << "Invalid choice. Please choose again." << std::endl;
        }
    }

    /* Calls the function that checks if the input is a valid binary number
            if (isValidBinary(slaveAdress))
            {
                std::cout << "You chose to change the slave adress to " << slaveAdress << std::endl;
                validChoice = true;
            }
            else
            {
                std::cout << "Invalid choice. Please choose again." << std::endl;
            }
            */

    validChoice = false;
    while (!validChoice)
    {
        std::cout << std::endl
                  << "Input the room number, valid room are 1-" << amountOfRooms << ":" << std::endl;
        std::cout << "If the slave is between rooms format it as 'X00N', where X and N are the two rooms" << std::endl;
        std::cout << "If the slave works with an ID-Sensor format it as 'X00X', where X is the room" << std::endl;

        std::cin >> roomNumber;
        if (roomNumber >= 1 && roomNumber <= 256256)
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
    std::string slaveAdressToSend = "B," + std::to_string(slaveAdress) + "," + std::to_string(roomNumber);
    std::cout << "Slave adress and room number: " << slaveAdressToSend << std::endl;

    /*
        const char *slaveAdressChar = slaveAdressToSend.c_str();

        // Send the slave adress and room number to the arduino
        arduino->writeSerialPort(slaveAdressChar, DATA_LENGTH);

        */

    nextMenu();
}

std::vector<std::string> PCHandler::getLog()
{
    std::vector<std::string> data;

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
        if (data.size() == amountOfUsers)
        {
            arduino->closeSerial();
        }
    }

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

void PCHandler::printLog(std::vector<int> log)
{
    clearScreen();

    // Print the highest room number for the person
    for (int i = 0; i < log.size(); i++)
    {
        std::cout << "Person " << (i + 1) << " is in Room " << log[i] << std::endl;
    }
}

void PCHandler::printRawData()
{
    std::vector<std::string> data = getLog();

    for (int i = 0; i < data.size(); i++)
    {
        std::cout << data[i] << std::endl;
    }

    nextMenu();
}

void PCHandler::setRooms()
{
    clearScreen();
    std::cout << "Enter the number of rooms: " << std::endl;
    std::cin >> amountOfRooms;
}

void PCHandler::setUsers()
{
    clearScreen();
    std::cout
        << "Enter the number of rooms: " << std::endl;
    std::cin >> amountOfUsers;
}

void PCHandler::initialiseSystem()
{

    const char *sendString = "D,init";

    arduino = new SerialPort(portName);

    arduino->isConnected();

    if (arduino->isConnected())
    {
        bool hasWritten = arduino->writeSerialPort(sendString, DATA_LENGTH);
        if (hasWritten)
        {
            std::cout << "Data written successfully." << std::endl;
        }
        else
        {
            std::cout << "Data was not written." << std::endl;
        }
    }

    arduino->~SerialPort(); // Destructor
    nextMenu();             // Next menu function doesnt work on const function
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

        if (roomValue < 1 || roomValue > amountOfRooms)
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
                  << "Input the room number 1 to " << amountOfRooms << ": " << std::endl;
        std::cin >> roomNumber;
        if (roomNumber >= 0 && roomNumber <= amountOfRooms)
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

    nextMenu();
}

void PCHandler::changeLog()
{

    std::vector<int> log = formatLog();
    int personNumber;
    int roomNumber;
    bool goBack = false;
    while (!goBack)
    {
        clearScreen();
        printLog(log);
        std::cout << std::endl
                  << "Select the person number you want to change the room of: " << std::endl;
        std::cout << "Press 0 to go back" << std::endl
                  << std::endl;
        std::cin >> personNumber;

        if (personNumber == 0)
        {
            goBack = true;
            break;
        }
        /* if (personNumber >= 1 && personNumber <= amountOfUsers)
         {
             std::cout << "Select the room number you want to change to: " << std::endl;
         }
         */

        std::cout << std::endl
                  << "Select the room number you want to change to: " << std::endl;
        std::cin >> roomNumber;

        if (roomNumber == 0)
        {
            goBack = true;
            break;
        }

        if (personNumber != 0 || roomNumber != 0)
        {
            log[personNumber - 1] = roomNumber;
        }
    }

    nextMenu();
}

void PCHandler::nextMenu()
{
    std::cout << std::endl
              << "Press any key to continue..." << std::endl;
    _getch();
}

void PCHandler::clearScreen() const
{
    // Clears the terminal and prints the title
    system("cls");                                                      // Code to clear the screen
    std::cout << "Intelligent Pattern Recognition System" << std::endl; // "IPRS SYSTEM
    std::cout << std::endl
              << std::endl;
}

std::vector<int> PCHandler::formatLog()
{
    std::vector<std::string> data = getLog();
    std::vector<int> highestRooms; // Vector to store the highest room numbers

    for (int j = 0; j < data.size(); j++)
    {
        data[j].push_back(' ');

        // Function to convert example to int array, split on " "
        std::string delimiter = " ";
        size_t pos = 0;
        std::string token;
        int i = 0;
        int arr[10];
        while ((pos = data[j].find(delimiter)) != std::string::npos)
        {
            token = data[j].substr(0, pos);
            arr[i] = std::stoi(token);
            data[j].erase(0, pos + delimiter.length());
            i++;
        }

        // Find the highest value in the array
        int highest = 0;
        int highestRoom = 0;
        for (int k = 0; k < amountOfRooms; k++)
        {
            if (arr[k] > highest)
            {
                highest = arr[k];
                highestRoom = k + 1; // Add +1 to get the room number
            }
        }

        // Save the highest room number in the vector
        highestRooms.push_back(highestRoom);
    }
    return highestRooms;
}

void updateLog(std::vector<int> log)
{
    std::ofstream myfile;
    myfile.open("log.txt");
    for (int i = 0; i < log.size(); i++)
    {
        myfile << log[i] << " ";
    }
    myfile.close();
}