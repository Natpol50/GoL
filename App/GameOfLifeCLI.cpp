#include "GameOfLifeCLI.hpp"
#include <string>

GameOfLifeCLI::GameOfLifeCLI(std::string inputPath, std::string outputDir, int maxIterations)
{
    fileManager = new FileManager(inputPath, outputDir);
    grid = new GridObject(fileManager->LoadInitialState());
    simManager = new SimManager(maxIterations);
}

int GameOfLifeCLI::run()
{
    int status = 0;
    do
    {
        status = simManager->iterate(grid, fileManager, true, true);
    } while (status == 0);

    if (status == 1)
    {
        std::cout << "Max iterations reached" << std::endl;
    }
    else if (status == 2)
    {
        std::cout << "Loop detected" << std::endl;
    }
    return status;
}