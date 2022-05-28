#include <iostream>
#include <string>
#include <utility>
#include <map>
#include "System/CoreFunctions.h"

CoreFunctions core = CoreFunctions();
std::map<std::pair<std::string, std::string>, std::string> UsersData;
std::pair<std::string, std::string> AdminAccountInfo;
std::string LoggedInUser;

std::string GetUserString(const std::string &preInputMessage)
{
    std::cout << preInputMessage;
    std::string Input = core.GetString();
    std::cout << "\n";
    return Input;
}

void AddNewUser(){
    system("cls");
    std::string Username        = GetUserString("Please Enter A Username: ");
    std::string Password        = GetUserString("Please Enter A Password: ");
    std::string SecretMessage   = GetUserString("Please Enter A Secret Message: ");
    
    // TODO: Add check that makes sure that we dont add a user that has the same username as one that previously exists

    UsersData.insert({std::make_pair(std::string(Username), std::string(Password)), SecretMessage});
    std::cout << "New User Added\n";
    core.WaitForKeyPress();
    system("cls");
}

bool UserIsAdmin(const std::string &Username, const std::string &Password){
    return (Username == AdminAccountInfo.first && Password == AdminAccountInfo.second);
}
bool UserIsAdmin(const std::string &Username){
    return (Username == AdminAccountInfo.first);
}

void DisplaySecretMessage(const std::string &Username){
    for (const auto &[UserDetails, Message] : UsersData){
        if (Username == UserDetails.first)
        {std::cout << Username << " your secret message is\n" << Message << "\n";}
    }
}

bool AttemptLogin(){
    system("cls");
    std::string LoginUsername = GetUserString("Please Enter A Username: ");
    std::string LoginPassword = GetUserString("Please Enter A Password: ");

    UserIsAdmin(LoginUsername, LoginPassword) ? LoggedInUser = AdminAccountInfo.first : LoggedInUser = "";

    if (LoggedInUser == ""){
        for (const auto &[UserDetails, Message] : UsersData){
            if (LoginUsername == UserDetails.first && LoginPassword == UserDetails.second){
                LoggedInUser = LoginUsername;
            }
        }
    }

    if (LoggedInUser == ""){std::cout << "Username and Password does not match a previously entered Username and Password\n\n";}
    return (LoggedInUser != "");
}

std::pair<std::string, std::string> FindUser(const std::string& Username){
    std::pair<std::string, std::string> user;
    user.first = "";
    user.second = "";
    for (const auto &[UserDetails, Message] : UsersData){
        if (Username == UserDetails.first){
            user = UserDetails;
        }
    }
    return user;
}

void ListUsers(){
    if (UsersData.size() == 0){std::cout << "There are no users available!\n";}
    for (const auto &[UserDetails, Message] : UsersData){
        std::cout << "Username: " << UserDetails.first << "\n";
    }
    core.WaitForKeyPress();
    system("cls");
}

void RemoveUser(){
    if (UsersData.size() == 0){std::cout << "There are no users available!\n";}
    else{
        std::cout << "To Remove A User, ";
        std::string UserToRemove = GetUserString("Please Enter A Username: ");
        std::pair<std::string, std::string> user = FindUser(UserToRemove);
        if(user.first!="") {
            UsersData.erase(user);
            std::cout << UserToRemove << " has been removed!\n";
        }
        else{std::cout << UserToRemove << " does not exist!\n";}
    }
    core.WaitForKeyPress();
    system("cls");
}

void AdminOptions(){
    system("cls");
    std::cout << "Welcome " << LoggedInUser << "\n";
    while (true)
    {
        std::cout << "Options:\n1. List Users\n2. Remove User\n";
        int Option = core.GetInt();
        switch (Option)
        {
        case 1:
        {
            ListUsers();
            break;
        }
        case 2:
        {
            RemoveUser();
            break;
        }
        default:
            break;
        }
    }
}

int main()
{
    system("cls");
    AdminAccountInfo = std::make_pair(std::string("ADMIN"), std::string("PASSWORD"));

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
            if (AttemptLogin()){
                if (!UserIsAdmin(LoggedInUser)){DisplaySecretMessage(LoggedInUser);}
                else {AdminOptions();}
            }
            core.WaitForKeyPress();
            system("cls");
            break;
        }
        default:
            break;
        }
    }
    return 0;
}
