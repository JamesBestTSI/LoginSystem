#ifndef ACCOUNTSYSTEM_H
#define ACCOUNTSYSTEM_H
#include <iostream>
#include <string>
#include <utility>
#include <map>
#include "System/CoreFunctions.h"

class AccountSystem{
private:
    CoreFunctions core = CoreFunctions();
    std::map<std::pair<std::string, std::string>, std::string> UsersData;
    const std::pair<std::string, std::string> AdminAccountInfo = std::make_pair(std::string("ADMIN"), std::string("PASSWORD"));
    std::string LoggedInUser;

public:
    void RunSystem();
    std::string GetUserString(const std::string &preInputMessage);
    void AddNewUser();
    bool UserIsAdmin(const std::string &Username, const std::string &Password);
    bool UserIsAdmin(const std::string &Username);
    void DisplaySecretMessage(const std::string &Username);
    bool Login();
    std::pair<std::string, std::string> FindUser(const std::string &Username);
    void ListUsers();
    void RemoveUser();
    void DisplayAdminOptions();
};
#endif