
#include "GameOfLifeCLI.hpp"

using namespace std;

GameOfLifeCLI::GameOfLifeCLI(){}

int GameOfLifeCLI::run()
{
    int status = 0;
    do
    {
        status = simManager.iterate(&grid, &fileManager;
    } while (status == 0);
    if (status == 1)
    {
        cout << "Max iterations reached" << endl;
    }
    else if (status == 2)
    {
        cout << "Loop detected" << endl;
    }
    return status;
}

int GameOfLifeCLI::initialize(string inpuPath, string outputDir, int maxIterations)
{
    fileManager = FileManager(inpuPath, outputDir);
    grid = fileManager.LoadInitialState();
    simManager = SimManager(maxIterations);
}
