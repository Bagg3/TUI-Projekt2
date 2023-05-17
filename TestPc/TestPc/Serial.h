// https://github.com/manashmandal/SerialPort

#pragma once
#include <windows.h>
#include <iostream>

#define ARDUINO_WAIT_TIME 2000
#define MAX_DATA_LENGTH 255

/*
PROTOCOL TO MASTER
A = Send log from master
B = New slave
C = Room connections
D = Initialise system
E = Amount of rooms and users
*/

class SerialPort
{
private:
    HANDLE handler;
    bool connected;
    COMSTAT status;
    DWORD errors;

public:
    explicit SerialPort(const char *portName);
    ~SerialPort();

    int readSerialPort(char *buffer, unsigned int buf_size);
    bool writeSerialPort(const char *buffer, unsigned int buf_size);
    bool isConnected();
    bool isDataAvailable();
    void closeSerial();
};