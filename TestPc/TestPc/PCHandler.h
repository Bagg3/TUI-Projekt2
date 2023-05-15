#ifndef PCHANDLER_H
#define PCHANDLER_H

// #pragma once
#include "User.h"
#include <Serial.h>

#define DATA_LENGTH 255

const char *portName = "\\\\.\\COM3";

// Declare a global object
std::string receivedData;

class PCHandler
{
public:
    PCHandler(std::string password = "admin");
    PCHandler(User *admin, SerialPort *arduino);

    void showMenu();
    void printData();
    void clearScreen() const;
    void changeSystem() const;
    void changeSlaves() const;

private:
    User user;
    User *userPtr;
    SerialPort *arduino;
};

#endif