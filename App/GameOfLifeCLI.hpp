
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
    GameOfLifeCLI() = default;
    int run();
    int initialize(std::string inpuPath, std::string outputDir, int maxIterations);
};


#endif // GAMEOFLIFECLI_HPP