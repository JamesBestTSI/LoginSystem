#include <iostream>
#include "CoreFunctions.h"
#include <string>
#include <conio.h>
#include <thread>
#include <chrono>

// Constructor
CoreFunctions::CoreFunctions(){};
// De-constructor
CoreFunctions::~CoreFunctions(){};

/// <summary>
/// Gets a number from the user.
///     Reads the data from the console,
///     Checks that it is a actual valid number,
///     Then returns that value.
/// </summary>
/// <returns>Number entered by user</returns>
int CoreFunctions::GetInt()
{
    while (true)
    {
        try
        {
            int input = -1;
            std::string consoleInput;
            std::cin >> consoleInput;
            std::cin.ignore();
            input = std::stoi(consoleInput);    
            return input;
        }
        catch (...)
        {
            std::cout << "Thats not a number!" << std::endl;
        }
    }
}

/// <summary>
/// Gets a number from the user.
///     Reads the data from the console,
///     Checks that it is a actual valid number,
///     Then returns that value.
/// </summary>
/// <returns>Number entered by user</returns>
int CoreFunctions::GetIntMinMax(int min, int max)
{
    int input = min-1;
    while (input < min || input > max)
    {
        std::cout << "Please enter a number between " << min << " and " << max << " :";
        input = GetInt();
        if (input < min || input > max)
        {std::cout << "\nNumber entered is outside of min and max range!\n";}
    }
    return input;
}

/// <summary>
/// Gets some string data from the user.
/// </summary>
/// <returns>The string they entered</returns>
std::string CoreFunctions::GetString(){
    std::string consoleInput;
    std::getline(std::cin, consoleInput);
    return consoleInput;
}


/// <summary>
/// Gets the first Char from the user.
/// </summary>
/// <returns>consoleInput[0]</returns>
char CoreFunctions::GetChar()
{
    std::string consoleInput = GetString();
    return consoleInput[0];
}

char CoreFunctions::WaitForKeyPress(){
    std::cout << "Press any key to continue...";
    return getch();
}

char CoreFunctions::WaitForKeyPress(int secondsToWait){
    std::chrono::steady_clock::time_point timerStart = std::chrono::steady_clock::now();
    while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - timerStart).count() < secondsToWait){
        if (_kbhit()){
            return getch();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return '\0';
}