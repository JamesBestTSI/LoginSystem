#include <iostream>
#include <string>
#include <utility>
#include <map>
#include "System/CoreFunctions.h"

CoreFunctions core = CoreFunctions();
std::map<std::pair<std::string, std::string>, std::string> UsersData;

std::string GetUserString(const std::string& preInputMessage){
    std::cout << preInputMessage;
    std::string Input = core.GetString();
    std::cout << "\n";
    return Input;
}

void AddNewUser(){
    std::string Username        = GetUserString("Please Enter A Username: ");
    std::string Password        = GetUserString("Please Enter A Password: ");
    std::string SecretMessage   = GetUserString("Please Enter A Secret Message: ");
    
    // TODO: Add check that makes sure that we dont add a user that has the same username as one that previously exists

    UsersData.insert({std::make_pair(std::string(Username), std::string(Password)), SecretMessage});
    std::cout << "New User Added\n";
    core.WaitForKeyPress();
    system("cls");
}


bool DisplaySecretMessage(const std::string& Username, const std::string& Password){
    for (const auto &[UserDetails, Message] : UsersData){
        if (Username == UserDetails.first && Password == UserDetails.second){
            std::cout << Username << " your secret message is\n" << Message << "\n\n";
            return true;
        }
    }
    return false;
}

void AttemptLogin(){
    std::string LoginUsername = GetUserString("Please Enter A Username: ");
    std::string LoginPassword = GetUserString("Please Enter A Password: ");

    if (!DisplaySecretMessage(LoginUsername, LoginPassword))
    {std::cout << "Username and Password does not match a previously entered Username and Password\n\n";}
    core.WaitForKeyPress();
    system("cls");
}

int main()
{
    UsersData.insert({std::make_pair(std::string("ADMIN"), std::string("PASSWORD")), "THIS IS THE SECRET ADMIN ACCOUNT"});
    while (true)
    {
        std::cout << "Options:\n1. Add User\n2. Login\n";
        int Option = core.GetInt();
        switch (Option)
        {
        case 1:
        {
            AddNewUser();
            break;
        }
        case 2:
        {
            AttemptLogin();
            break;
        }
        default:
            break;
        }
    }
    return 0;
}
