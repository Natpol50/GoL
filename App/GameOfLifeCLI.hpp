#ifndef GAMEOFLIFECLI_HPP
#define GAMEOFLIFECLI_HPP

#include <iostream>
#include <string>
#include "Managers/SimManager.hpp"
#include "Managers/FileManager.hpp"

class GameOfLifeCLI
{
private:
    FileManager* fileManager;
    SimManager* simManager;
    GridObject* grid;

public:
    GameOfLifeCLI(std::string inputPath, std::string outputDir, int maxIterations);
    int run();
};

#endif // GAMEOFLIFECLI_HPP