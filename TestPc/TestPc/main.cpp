#include <iostream>
#include <string>
#include "User.h"
#include "PCHandler.h"

/*
#define DATA_LENGTH 255


std::string receivedData;
*/

// const char *portName = "\\\\.\\COM3";

/*
TODO LIST

- Change the clearScreen function to be with userPtr

*/

int main()
{
	// User user("admin");
	//  SerialPort arduino(portName);

	LAV EN FUNKTION SOM HEDDER FORMAT LOG
		PCHandler PC("admin");
	PC.clearScreen();
	PC.showMenu();

	return 0;
}

/*
#include "Serial.h" // Library described above
#include <vector>



// Declare a global object
SerialPort *arduino;
std::string receivedData;


int main()
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
				// std::cout << receivedData << std::endl;

				data.push_back(receivedData);
				receivedData.clear();
				if (data.size() == 2)
				{
					arduino->closeSerial();
				}
			}
		}
	}

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

		std::cout << highest << std::endl;
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

	/*
	std::string Bruger1;

	for (size_t i = 0; i < data.size(); i++) {
		std::cout << data[i] << std::endl;
		char* dataPtr = &data[i][0];

		char* ptr = strtok(data[i], ",");

		while (dataPtr != ",") {
			;
			Bruger1 = *dataPtr;
			dataPtr++;
		}

	}

	std::cout << Bruger1 << std::endl;


	return 0;
}

// else std::cerr << "Error occured reading data" << "\n";
// Sleep(50);
*/

/*
# include<windows.h>
HANDLE console = GetStdHandle(STD_INPUT_HANDLE);
DWORD consoleMode;
GetConsoleMode(console, &consoleMode);

//Remove echo from console
SetConsoleMode(console, consoleMode & ~ENABLE_ECHO_INPUT);

// Set console to default
SetConsoleMode(console, consoleMode);
*/