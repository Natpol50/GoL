
#include "GameOfLifeCLI.hpp"

using namespace std;

GameOfLifeCLI::GameOfLifeCLI(string inpuPath, string outputDir, int maxIterations)
{
    fileManager = FileManager(inpuPath, outputDir);
    grid = fileManager.LoadInitialState();
    simManager = SimManager(maxIterations);
}

int GameOfLifeCLI::run()
{
    int status = 0;
    do
    {
        status = simManager.iterate(&grid, &fileManager, true, true);
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
