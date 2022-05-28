#include "AccountSystem.h"

void AccountSystem::RunSystem(){
    while (true){
        std::cout << "Options:\n1. Add User\n2. Login\n";
        int Option = core.GetInt();
        switch (Option)
        {
        case 1:{    AddNewUser(); break;}
        case 2:{    if (Login())
                    {
                        if (UserIsAdmin(LoggedInUser))  {DisplayAdminOptions();}
                        else                            {DisplaySecretMessage(LoggedInUser);}
                    }
            core.WaitForKeyPress();
            system("cls"); break;}
        default:{   break;}
        }
    }
}

/**
 * @brief Adds a new user to the list of saved users
 */
void AccountSystem::AddNewUser(){
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

/**
 * @brief Gets some string data from the user after displaying the preInputMessage
 * 
 * @param preInputMessage The message to be displayed before asking for input
 * @return std::string The input the user gave us
 */
std::string AccountSystem::GetUserString(const std::string &preInputMessage){
    std::cout << preInputMessage;
    std::string Input = core.GetString();
    std::cout << "\n";
    return Input;
}

/**
 * @brief Gets login details from the user and then processes it to see if the user was able to log in
 * 
 * @return true If details provided match one of those in the list of users
 * @return false If details provided do not match any of those in our list of users
 */
bool AccountSystem::Login(){
    system("cls");
    std::string LoginUsername = GetUserString("Please Enter A Username: ");
    std::string LoginPassword = GetUserString("Please Enter A Password: ");

    UserIsAdmin(LoginUsername, LoginPassword) ? LoggedInUser = AdminAccountInfo.first : LoggedInUser = "";

    if (LoggedInUser == "")    {
        for (const auto &[UserDetails, Message] : UsersData)        {
            if (LoginUsername == UserDetails.first && LoginPassword == UserDetails.second)
            {LoggedInUser = LoginUsername;}
        }
    }

    if (LoggedInUser == "")
    {std::cout << "Username and Password does not match a previously entered Username and Password\n\n";}
    return (LoggedInUser != "");
}

/**
 * @brief Checks to see if the user and password provided match that of the Admin account
 * 
 * @param Username The username to check against the Admin Username
 * @param Password The password to check against the Admin password
 * @return true If both match the Admin Username and Password
 * @return false If one of them doesn't match the Admin Username and Password
 */
bool AccountSystem::UserIsAdmin(const std::string &Username, const std::string &Password){
    return (Username == AdminAccountInfo.first && Password == AdminAccountInfo.second);
}

/**
 * @brief Checks to see if the username provided matches that of the Admin username
 * 
 * @param Username The username to check for a match
 * @return true If the Username Matches
 * @return false If the username doesn't match
 */
bool AccountSystem::UserIsAdmin(const std::string &Username){
    return (Username == AdminAccountInfo.first);
}

/**
 * @brief Displays the secret message for the username
 * 
 * @param Username The username we want to find the secret message from
 */
void AccountSystem::DisplaySecretMessage(const std::string &Username){
    for (const auto &[UserDetails, Message] : UsersData){
        if (Username == UserDetails.first)
        {std::cout << Username << " your secret message is\n"<< Message << "\n";}
    }
}

/**
 * @brief Finds a user in the list with the matching username and then returns the user and its password
 * 
 * @param Username The username that we want to find in our list
 * @return std::pair<std::string, std::string> The username, Password of that user (["" , ""] if no user found)
 */
std::pair<std::string, std::string> AccountSystem::FindUser(const std::string &Username){
    std::pair<std::string, std::string> user;
    user.first = "";
    user.second = "";
    for (const auto &[UserDetails, Message] : UsersData){
        if (Username == UserDetails.first)
        {user = UserDetails;}
    }
    return user;
}

/**
 * @brief Lists all the users that we have on record
 */
void AccountSystem::ListUsers(){
    if (UsersData.size() == 0)
    {std::cout << "There are no users available!\n";}
    for (const auto &[UserDetails, Message] : UsersData)
    {std::cout << "Username: " << UserDetails.first << "\n";}
    core.WaitForKeyPress();
    system("cls");
}

/**
 * @brief Asks for a username to remove from the list of users, and then removes that user if it exists
 */
void AccountSystem::RemoveUser(){
    if (UsersData.size() == 0)
    {std::cout << "There are no users available!\n";}
    else{
        std::cout << "To Remove A User, ";
        std::string UserToRemove = GetUserString("Please Enter A Username: ");
        std::pair<std::string, std::string> user = FindUser(UserToRemove);
        if (user.first != ""){
            UsersData.erase(user);
            std::cout << UserToRemove << " has been removed!\n";
        }
        else
        {std::cout << UserToRemove << " does not exist!\n";}
    }
    core.WaitForKeyPress();
    system("cls");
}

/**
 * @brief Displays the admin Options for use
 */
void AccountSystem::DisplayAdminOptions(){
    system("cls");
    std::cout << "Welcome " << LoggedInUser << "\n";
    while (true){
        std::cout << "Options:\n1. List Users\n2. Remove User\n";
        int Option = core.GetInt();
        switch (Option){
            case 1:{ListUsers();break;}
            case 2:{RemoveUser();break;}
            default:{break;}
        }
    }
}