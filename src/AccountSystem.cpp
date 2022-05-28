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
    LoggedInUser = "";
    std::string LoginUsername = GetUserString("Please Enter A Username: ");
    std::string LoginPassword = GetUserString("Please Enter A Password: ");

    // Check if Admin Account Entered
    UserIsAdmin(LoginUsername, LoginPassword) ? LoggedInUser = AdminAccountInfo.first : LoggedInUser = "";

    // If not admin, check if user exists
    if (LoggedInUser == "")    {
        for (const auto &[UserDetails, Message] : UsersData)        {
            if (LoginUsername == UserDetails.first && LoginPassword == UserDetails.second)
            {LoggedInUser = LoginUsername;}
        }
    }

    // If details entered failed
    if (LoggedInUser == ""){
        std::cout << "Username and Password does not match a previously entered Username and Password\n\n";
        LockAccount(LoginUsername);
    }
    // Finally check that the account is not locked out
    else if(IsAccountLocked(LoginUsername)){
        LoggedInUser = "";
    }    
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
        std::cout << "Options:\n1. List Users\n2. Remove User\n3. Unlock Account\n";
        int Option = core.GetInt();
        switch (Option){
            case 1:{ListUsers();break;}
            case 2:{RemoveUser();break;}
            case 3:{UnlockAccount();break;}
            default:{break;}
        }
    }
}

/**
 * @brief Locks an account name for 1 minute
 * 
 * @param Username The account name to lock
 */
void AccountSystem::LockAccount(std::string Username){
    bool AccountAlreadyLocked = false;
    for (const auto &[LockedUsername, LockedStartTime] : LockedAccounts){
        if(Username == LockedUsername){
            long long secondsPassed = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - LockedStartTime).count();
            if (secondsPassed < 60){
                AccountAlreadyLocked = true;
                std::cout << "Account is currently locked for " << 60 - secondsPassed << " seconds!";
            }
            else
            {LockedAccounts.erase(Username);}
        }
    }
    if(!AccountAlreadyLocked){
        LockedAccounts.insert({Username, std::chrono::steady_clock::now()});
        std::cout << "Account has been locked for 1 minute!\n";
    }
}

/**
 * @brief Used to unlock an account.
 */
void AccountSystem::UnlockAccount(){
    if (LockedAccounts.size() == 0)
    {std::cout << "There are no locked accounts available!\n";}
    else
    {
        std::cout << "To Unlock An Account, ";
        std::string UserToUnlock = GetUserString("Please Enter A Username: ");
        bool unlocked = false;
        for (const auto &[LockedUsername, LockedStartTime] : LockedAccounts){
            if (LockedUsername == UserToUnlock){
                LockedAccounts.erase(LockedUsername);
                std::cout << "Account Unlocked!\n";
                unlocked = true;
            }
        }
        if (!unlocked)
        {std::cout << "Account was not locked!\n";}
    }
    core.WaitForKeyPress();
    system("cls");
}

/**
 * @brief Checks to see if the account is locked out, 
 * while looping through locked accounts, also clears accounts that have passed the 1 minute timer
 * 
 * @param Username Account name we want to check if its locked
 * @return true if locked out
 * @return false if not locked out
 */
bool AccountSystem::IsAccountLocked(const std::string& Username){
    for (const auto &[LockedUsername, LockedStartTime] : LockedAccounts){
        long long secondsPassed = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - LockedStartTime).count();

        if (secondsPassed > 60)
        {LockedAccounts.erase(LockedUsername);}

        else if (Username == LockedUsername){
            std::cout << "Account is currently locked for " << 60 - secondsPassed << " seconds!";
            return true;
        }
    }
    return false;
}