#ifndef PCHANDLER_H
#define PCHANDLER_H

#pragma once
#include "User.h"
#include "Serial.h"
#include "dbHandler.h"
#include <vector>

class PCHandler
{
public:
    PCHandler(std::string password = "admin");
    PCHandler(User *admin, SerialPort *arduino, dbHandler *dataBase);

    void showMenu();

    void printData();

    std::vector<std::string> getLog();
    std::vector<int> formatLog();
    void printLog(std::vector<int> log);
    void printRawData();

    void changeSystem();
    void addSlave();
    void setRooms();
    void setUsers();
    void selectRoomConnection();

    void calibrateSystem();
    void changeLog();

    void nextMenu();
    bool isValidBinary(const std::string &input);
    // void clearScreen() const;
    bool isValidRoom(const std::string &input);

    void updateLog(std::vector<int> log);

    void printSystemInfo();

    void checkIfInitialised();

private:
    int amountOfRooms;
    int amountOfUsers;
    User user;
    User *userPtr;
    SerialPort *arduino;
    dbHandler *db;
    const char *portName = "\\\\.\\COM3";
};

#endif
