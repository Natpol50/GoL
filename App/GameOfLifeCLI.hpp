
#ifndef GAMEOFLIFECLI_HPP
#define GAMEOFLIFECLI_HPP

#include <iostream>
#include "Managers/FileManager.hpp"
#include "Managers/SimManager.hpp"
#include "Grid/GridObject.hpp"


class GameOfLifeCLI
{
private:
    FileManager fileManager;
    SimManager simManager;
    GridObject grid;
public:
    GameOfLifeCLI(string inpuPath, string outputDir, int maxIterations);
    int run();
};


#endif // GAMEOFLIFECLI_HPP