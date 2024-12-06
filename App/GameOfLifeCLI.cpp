#include "GameOfLifeCLI.hpp"

GameOfLifeCLI::GameOfLifeCLI(std::string inputPath, std::string outputDir, int maxIterations)
{
    fileManager = new FileManager(inputPath, outputDir);
    grid = new GridObject(fileManager->LoadInitialState());
    simManager = new SimManager(maxIterations);
}

GameOfLifeCLI::~GameOfLifeCLI()
{
    delete fileManager;
    delete grid;
    delete simManager;
}

int GameOfLifeCLI::run()
{
    int status = 0;
    do {
        clearScreen();
        std::cout << "Current iteration: " << simManager->getCurrentIterationCount() << std::endl;
        status = simManager->iterate(grid, fileManager, true, true);
    } while (status == 0);

    if (status == 1) {
        std::cout << "\nMax iterations reached" << std::endl;
    }
    else if (status == 2) {
        std::cout << "\nLoop detected" << std::endl;
    }
    
    return status;
}