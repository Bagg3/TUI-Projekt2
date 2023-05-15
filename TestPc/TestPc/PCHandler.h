#ifndef PCHANDLER_H
#define PCHANDLER_H

// #pragma once
#include "User.h"

class PCHandler
{
public:
    PCHandler(std::string password = "admin");
    // PCHandler(User* user_);

    void showMenu();
    void printData();
    void clearScreen() const;
    void changeSystem() const;
    void changeSlaves() const;

private:
    User user;
};

#endif