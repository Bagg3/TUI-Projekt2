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
/*
PCHandler::PCHandler(std::string password)
{
	User admin(password);

	amountOfRooms = 10;
	amountOfUsers = 10;
}
*/

PCHandler::PCHandler(User *admin, SerialPort *arduino, dbHandler *dataBase)
{
	// Setting up objects and dependcies
	userPtr = admin;
	this->arduino = arduino;
	db = dataBase;

	// Setting the amount of rooms and users from database
	amountOfRooms = std::stoi(db->findData("rooms.txt", false));
	amountOfUsers = std::stoi(db->findData("users.txt", false));
	db->setSaveOnline(db->getSaveData());
}

void PCHandler::showMenu()
{
	running = true; // Used to turn off the program
	while (running)
	{
		int choice = 0;

		// Login function
		userPtr->login();

		// Checks to see if the system has been initialised
		checkIfInitialised();

		while (userPtr->isLoggedIn())
		{
			userPtr->clearScreen();
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
				showChangeOptions();
				break;
			case 3:
				initialiseSystem();
				break;
			case 4:
				changeLog();
				break;
			case 5:
				userPtr->changePassword();
				break;
			case 6:
				userPtr->logout();
				break;
			case 7:;
				exit();
				break;
			default:
				std::cout << "Invalid choice. Please choose again." << std::endl;
				break;
			}

			// Only clears the screen if program is running
			std::cout << std::endl;
			if (running)
				userPtr->clearScreen();
		}
		arduino->~SerialPort();
	}
}

void PCHandler::printData()
{
	int choice = 0;
	bool goBack = false;
	std::vector<int> log;

	while (!goBack)
	{
		userPtr->clearScreen();
		// The various print options
		std::cout << "Please choose an option:" << std::endl;
		std::cout << "1. Print Formatet Log" << std::endl;
		std::cout << "2. Print Raw Data" << std::endl;
		std::cout << "3. Print System Info" << std::endl;
		std::cout << "4. Go Back" << std::endl
				  << std::endl;

		std::cin >> choice;

		switch (choice)
		{
		case 1:
			userPtr->clearScreen();
			std::cout << "Fechting data..." << std::endl;
			log = formatLog();
			printLog(log);
			nextMenu();
			break;
		case 2:
			userPtr->clearScreen();
			std::cout << "Fechting data..." << std::endl;
			printRawData();
			break;
		case 3:
			userPtr->clearScreen();
			printSystemInfo();
			break;
		case 4:
			goBack = true;
			break;
		default:
			std::cout << "Invalid choice. Please choose again." << std::endl;
			break;
		}

		std::cout << std::endl;
	}
}

void PCHandler::showChangeOptions()
{

	int choice = 0;
	bool goBack = false;

	while (!goBack)
	{
		userPtr->clearScreen();
		// The various change system options
		std::cout << "Please choose an option:" << std::endl;
		std::cout << "1. Add a new slave" << std::endl;
		std::cout << "2. Select room connection" << std::endl;
		std::cout << "3. Calibrate the system" << std::endl;
		// std::cout << "4. Change name of rooms or persons" << std::endl;
		std::cout << "4. Select save online" << std::endl;
		std::cout << "5. Go Back" << std::endl
				  << std::endl;

		std::cin >> choice;

		switch (choice)
		{
		case 1:
			userPtr->clearScreen();
			addSlave();
			break;
		case 2:
			userPtr->clearScreen();
			selectRoomConnection();
			break;
		case 3:
			userPtr->clearScreen();
			calibrateSystem();
			break;
		case 4:
			userPtr->clearScreen();
			selectSaveOnline();
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
	userPtr->clearScreen();

	// Instantiate of variables
	bool validChoice = false;
	int slaveAdress;
	int roomNumber;

	// Makes sure the user inputs a valid number
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

	validChoice = false;
	while (!validChoice)
	{
		std::cout << std::endl
				  << "Input the room number, valid room are 1-" << amountOfRooms << ":" << std::endl;
		std::cout << "If the slave is between rooms format it as 'X00N', where X and N are the two rooms" << std::endl;
		std::cout << "If the slave works with an ID-Sensor format it as 'X00X', where X is the room" << std::endl;

		std::cin >> roomNumber;
		// Valid room numbers are 1-256256 because of 256 256 is the highest combination
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
	std::string slaveAdressToSend = "B," + std::to_string(slaveAdress) + "," + std::to_string(roomNumber) + "\0";
	std::cout << "Slave adress and room number: " << slaveAdressToSend << std::endl;

	// Converts the string to a char array and sends it to the arduino
	sendData(slaveAdressToSend.c_str());

	nextMenu();
}

std::vector<std::string> PCHandler::getLog(bool connect)
{
	std::vector<std::string> data;
	bool hasBeenConnected = false; // Checks if the arduino has been connected before

	// If the variable connect is true, the function will try to connect to the arduino
	if (connect)
	{

		sendData(logRequest);

		// If the arduino is not connected, it will try to connect
		if (!arduino->isConnected())
		{
			arduino = new SerialPort(portName);
		}

		std::cout << "Is connected: " << arduino->isConnected() << std::endl;

		if (arduino->isConnected())
		{
			hasBeenConnected = true; // Sets the variable to true

			// Sets up the variables for the while loop
			char receivedChar[DATA_LENGTH];
			std::string receivedData;

			bool disconnect = false;
			while (!disconnect)
			{
				// Reads the serial port and saves the data in the variables
				int hasRead = arduino->readSerialPort(receivedChar, DATA_LENGTH);

				// If the data is not empty, it will be saved in the vector, sort on "\n"
				if (hasRead > 0)
				{
					for (int i = 0; i < hasRead; i++)
					{
						if (receivedChar[i] != '\n')
						{
							receivedData += receivedChar[i];
						}
						else
						{
							data.push_back(receivedData);
							receivedData.clear();
						}
					}
				}
				// Once the desired amount of data has been received, the serial port will be closed
				if (data.size() == amountOfUsers || !arduino->isConnected())
				{
					disconnect = true;
				}
			}
		}

		std::cout << "Has been connected: " << hasBeenConnected << std::endl;
	}

	// If the arduino has not been connected, the data will be read from the log file
	if (!hasBeenConnected)
	{
		std::string log;
		log = db->findData("log.txt", false);

		// Convert the string to a vector of strings with " " as delimiter for each index in the vector
		std::stringstream ss(log);
		std::string temp;
		while (ss >> temp)
		{
			data.push_back(temp);
		}
	}

	return data;
}

/*
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
*/
void PCHandler::printLog(std::vector<int> log, bool clrScreen)
{

	if (clrScreen)
		userPtr->clearScreen();

	// Print the highest room number for the person
	for (int i = 0; i < log.size(); i++)
	{
		std::cout << "Person " << (i + 1) << " is in Room " << log[i] << std::endl;
	}
}

void PCHandler::printRawData()
{
	std::vector<std::string> data = getLog();

	userPtr->clearScreen();

	// Prints the raw data from the log
	for (int i = 0; i < data.size(); i++)
	{
		std::cout << data[i] << std::endl;
	}

	nextMenu();
}

void PCHandler::setRooms()
{
	bool validChoice = false;
	while (!validChoice)
	{
		userPtr->clearScreen();
		std::cout << "Enter the number of rooms: " << std::endl;
		std::cin >> amountOfRooms;
		if (amountOfRooms >= 1 && amountOfRooms <= 256)
		{
			validChoice = true;
			break;
		}
		else
		{
			std::cout << "Invalid choice. Please choose again." << std::endl;
		}
	}
	// Saves the data in the database
	db->saveData("rooms.txt", std::to_string(amountOfRooms), false);
}

void PCHandler::setUsers()
{
	bool validChoice = false;
	while (!validChoice)
	{
		userPtr->clearScreen();
		std::cout << "Enter the number of user: " << std::endl;
		std::cin >> amountOfRooms;
		if (amountOfUsers >= 1 && amountOfUsers <= 256)
		{
			validChoice = true;
			break;
		}
		else
		{
			std::cout << "Invalid choice. Please choose again." << std::endl;
		}
	}
	// Saves the data in the database
	db->saveData("users.txt", std::to_string(amountOfUsers), false);
}

void PCHandler::sendData(const char *sendString)
{
	// If the arduino is not connected, it will be connected
	if (!arduino->isConnected())
	{
		arduino = new SerialPort(portName);
	}

	// If the arduino is connected, the data will be sent
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
}

void PCHandler::calibrateSystem()
{
	// Uses the sendData function to send the calibration request to the arduino
	sendData(calibrateRequest); // Calibrate request is a const char* defined in the header file

	bool dataRead = false;
	std::string receivedData;
	char receivedChar[DATA_LENGTH];
	int hasRead = 0;

	if (!arduino->isConnected())
	{
		arduino = new SerialPort(portName);
	}

	while (!dataRead)
	{
		hasRead = arduino->readSerialPort(receivedChar, DATA_LENGTH);
		if (hasRead > 0)
		{
			for (int i = 0; i < hasRead; i++)
			{
				if (receivedChar[i] != '\n')
				{
					receivedData += receivedChar[i];
				}
				else
				{
					// Process receivedData here instead of clearing it
					std::cout << "Received data: " << receivedData << std::endl;

					receivedData.clear();
					dataRead = true;
				}
			}
		}
	}

	nextMenu(); // Next menu function doesnt work on const function
}

bool PCHandler::isValidRoom(const std::string &input)
{

	std::stringstream ss(input); // Create a stringstream to extract values separated by commas
	std::string segment;		 // Store each segment between commas

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
	userPtr->clearScreen();
	int roomNumber;
	std::cout << "Select room to specify its connections:" << std::endl;
	bool validChoice = false;
	std::string roomConnections;

	// Asks the user to input the room number and the rooms it is connected to
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

	// Sends the data to the arduino
	std::string data = "C," + std::to_string(roomNumber) + "," + roomConnections;
	sendData(data.c_str());
	nextMenu();
}

void PCHandler::changeLog()
{
	std::vector<int> log = formatLog(false);
	int personNumber;
	int roomNumber;
	bool goBack = false;

	// Asks the user to input the person number and the room number
	while (!goBack)
	{
		bool validChoice = true;
		userPtr->clearScreen();
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
		else if (personNumber < 0 || personNumber > amountOfUsers)
		{
			std::cout << "Invalid person number. Please try again." << std::endl;
			validChoice = false;
			continue;
		}

		if (validChoice)
		{
			std::cout << std::endl
					  << "Select the room number you want to change to, valid rooms are 1-" << amountOfRooms << ":" << std::endl;
			std::cin >> roomNumber;

			if (roomNumber == 0)
			{
				goBack = true;
				break;
			}
			else if (roomNumber < 1 || roomNumber > amountOfRooms)
			{
				std::cout << "Invalid room number. Please try again." << std::endl;
				continue;
			}

			log[personNumber - 1] = roomNumber;
		}
	}

	// Sends the data to the log file
	updateLog(log);
	nextMenu();
}

void PCHandler::nextMenu()
{
	// Waits for the user to press a key before continuing
	std::cout << std::endl
			  << "Press any key to continue..." << std::endl;
	_getch();
}

std::vector<int> PCHandler::formatLog(bool connect)
{
	std::vector<std::string> data = getLog(connect);
	std::vector<int> log; // Vector to store the room numbers with highest probability

	// If the data is not connected to the arduino, the data is already formatted 256 is max value
	if (data[0].length() < 4)
	{
		for (const std::string &line : data)
		{
			int value = std::stoi(line);
			log.push_back(value);
		}
	}
	else
	{
		// If the data is connected to the arduino, the data is formatted as "roomNumber:probability"
		for (int j = 0; j < data.size(); j++)
		{

			data[j].push_back(' '); // Add a space at the end of the string to make it so the last number is also added to the array

			// Function to convert example to int array, split on " "
			std::string delimiter = " "; // Define the delimiter
			size_t pos = 0;				 // Initialize the position variable for finding the delimiter
			std::string token;			 // Initialize a string variable to store the extracted token
			int i = 0;
			int arr[10]; // Declare an integer array to store the converted values

			// Loop through the string to extract tokens delimited by a space
			while ((pos = data[j].find(delimiter)) != std::string::npos)
			{
				token = data[j].substr(0, pos);				// Extract the token from the beginning to the delimiter position
				arr[i] = std::stoi(token);					// Convert the token to an integer and store it in the array
				data[j].erase(0, pos + delimiter.length()); // Remove the extracted token and the delimiter from the string
				i++;
			}

			// Find the highest value in the array
			int highest = 0;
			int highestRoom = 0;
			// Loop through the array to find the highest value
			for (int k = 0; k < amountOfRooms; k++)
			{
				if (arr[k] > highest)
				{
					highest = arr[k];
					highestRoom = k + 1; // Add +1 to get the room number
				}
			}

			// Save the highest room number in the vector
			log.push_back(highestRoom);
		}
	}
	updateLog(log); // Update the log with the highest room numbers
	return log;
}

void PCHandler::updateLog(std::vector<int> log)
{
	// Convert the log to a string
	std::string logString = "";
	for (int i = 0; i < log.size(); i++)
	{
		logString += std::to_string(log[i]);
		logString += " ";
	}
	// Save the log to the log file
	db->saveData("log.txt", logString, false);
}

void PCHandler::printSystemInfo()
{ // Prints the system information
	std::cout << "System information: " << std::endl;
	std::cout << "Amount of rooms: " << amountOfRooms << std::endl;
	std::cout << "Amount of users: " << amountOfUsers << std::endl
			  << std::endl;
	std::cout << "Current Log from database: " << std::endl;
	std::vector<int> log = formatLog(false);
	printLog(log, false);
	nextMenu();
}

void PCHandler::checkIfInitialised()
{
	// Checks if the system is initialised by checking if the amount of rooms and users is not 0
	if (db->findData("rooms.txt", false) != "" || db->findData("users.txt", false) != "")
	{
		amountOfRooms = std::stoi(db->findData("rooms.txt", false));
		amountOfUsers = std::stoi(db->findData("users.txt", false));
	}
	else
	{
		std::cout << "Do you wan to initialise the system?" << std::endl;
		std::cout << "1. Yes" << std::endl;
		std::cout << "2. No" << std::endl
				  << std::endl;
		int choice;
		std::cin >> choice;

		if (choice == 1)
		{
			initialiseSystem();
		}
	}
}

void PCHandler::initialiseSystem()
{
	int amountOfSlaves;
	std::cout << "Initialising system..." << std::endl;

	// Sets the amount of rooms and users
	setRooms();
	setUsers();

	std::string data = "E," + std::to_string(amountOfRooms) + "," + std::to_string(amountOfUsers) + "\0";

	sendData(data.c_str());

	//   userPtr->clearScreen();

	std::cout << std::endl
			  << "Define how many slaves you want to set: " << std::endl;

	std::cin >> amountOfSlaves;

	for (int i = 0; i < amountOfSlaves; i++)
	{
		addSlave();
	}
	nextMenu();
}

void PCHandler::selectSaveOnline()
{
	// Prints the current save online setting and asks the user if they want to change it
	std::cout << "Currently the data";
	if (db->getSaveOnline() == true)
		std::cout << " is";

	else
		std::cout << " is not";

	std::cout << " saved online." << std::endl;
	std::cout << "Do you want to save the data online?" << std::endl
			  << std::endl;
	std::cout << "1. Yes" << std::endl;
	std::cout << "2. No" << std::endl
			  << std::endl;
	int choice;
	std::cin >> choice;

	// If the user wants to save the data online, the setting is changed to true
	if (choice == 1)
	{
		db->setSaveOnline(true);
		db->saveData("saveSettings.txt", "true", false);
	}
	else
	{
		db->setSaveOnline(false);
		db->saveData("saveSettings.txt", "false", false);
	}
}

void PCHandler::exit()
{
	running = false;
	userPtr->logout();
}
