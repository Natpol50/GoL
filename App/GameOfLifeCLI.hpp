#ifndef GAMEOFLIFECLI_HPP
#define GAMEOFLIFECLI_HPP

#include <iostream>
#include <string>
#ifdef _WIN32
    #include <windows.h>
#endif
#include "Managers/SimManager.hpp"

class GameOfLifeCLI {
private:
    FileManager* fileManager;
    SimManager* simManager;
    GridObject* grid;
    
    void clearScreen() {
        #ifdef _WIN32
            HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
            COORD coord = {0, 0};
            DWORD count;
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(hStdOut, &csbi);
            FillConsoleOutputCharacter(hStdOut, ' ', 
                csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
            SetConsoleCursorPosition(hStdOut, coord);
        #else
            std::cout << "\033[2J\033[1;1H"; // ANSI escape codes for Unix-like systems
        #endif
    }

public:
    GameOfLifeCLI(std::string inputPath, std::string outputDir, int maxIterations);
    ~GameOfLifeCLI();
    int run();
};

#endif // GAMEOFLIFECLI_HPP