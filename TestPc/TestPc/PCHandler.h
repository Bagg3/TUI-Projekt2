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
    void printLog();
    void printRawData();

    void selectRoomConnection();
    void showMenu();
    void printData();
    void changeSystem();
    void addSlave();
    void setRooms();
    void setUsers();
    void initialiseSystem() const;
    bool isValidBinary(const std::string &input);
    void clearScreen() const;
    bool isValidRoom(const std::string &input);
    void changeLog();
    void nextMenu();

private:
    int amountOfRooms;
    int amountOfUsers;
    User user;
    User *userPtr;
    SerialPort *arduino;
};

#endif
