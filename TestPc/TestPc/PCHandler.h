#ifndef PCHANDLER_H
#define PCHANDLER_H

#pragma once
#include "User.h"
#include "Serial.h"
#include <vector>

class PCHandler
{
public:
    PCHandler(std::string password = "admin");
    PCHandler(User *admin, SerialPort *arduino);

    std::vector<std::string> getLog();
    void printLog(std::vector<std::string> data);
    void printRawData(std::vector<std::string> data);

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