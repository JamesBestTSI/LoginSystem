#ifndef COREFUNCTIONS_H
#define COREFUNCTIONS_H
#include <string>

class CoreFunctions{
    public:
        CoreFunctions();
        ~CoreFunctions();

        int GetInt();
        int GetIntMinMax(int min, int max);
        std::string GetString();
        char GetChar();
        char WaitForKeyPress();
        char WaitForKeyPress(int secondsToWait);
};
#endif