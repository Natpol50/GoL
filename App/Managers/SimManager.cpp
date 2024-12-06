#include "SimManager.hpp"

SimManager::SimManager(int maxIterations) : maxIterations(maxIterations), iteractionCount(0) {}

int SimManager::getCurrentIterationCount()
{
    return iteractionCount;
}

int SimManager::iterate(GridObject* grid, FileManager* FileMan,  bool Save, bool Hash)
{
    iteractionCount++;
    grid->update();
    if (Save)
    {
        std::string fileName = "Iteration" + std::to_string(iteractionCount);
        FileMan->SaveState(grid, fileName);
    }
    if (iteractionCount >= maxIterations && maxIterations != 0)
    {
        return 1;
    }
    else if (Hash == 1 && !history.hashAndCheck(grid))
    {
        return 2;
    }
    return 0;
}