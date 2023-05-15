#include <iostream>
#include <string>
#include "User.h"
#include "PCHandler.h"
#include "Serial.h" // Library described above
#include <vector>

#define DATA_LENGTH 255

const char* portName = "\\\\.\\COM3";

// Declare a global object
SerialPort* arduino;
std::string receivedData;

int main()
{
	std::vector <std::string> data;
	arduino = new SerialPort(portName);
	arduino->isConnected();
	std::cout << "Is connected: " << arduino->isConnected() << std::endl;

	while (arduino->isConnected()) {
		char receivedChar;
		int hasRead = arduino->readSerialPort(&receivedChar, 1);
		if (hasRead) {
			if (receivedChar != '\n') {
				receivedData += receivedChar;
			}
			else {
				//std::cout << receivedData << std::endl;

				data.push_back(receivedData);
				receivedData.clear();
				if (data.size() == 10) {
					arduino->closeSerial();
				}
			}
		}

	}



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

//else std::cerr << "Error occured reading data" << "\n";
//Sleep(50);

	/*
		PCHandler PC("admin");
		PC.clearScreen();
		std::cout << "Welcome to the IPRS system" << std::endl;
		PC.showMenu();

		return 0;

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