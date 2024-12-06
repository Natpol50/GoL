#include "SimManager.hpp"

SimManager::SimManager(int maxIterations)
{
    this->maxIterations = maxIterations;
    this->iteractionCount = 0;
}

int SimManager::getCurrentIterationCount()
{
    return iteractionCount;
}

int SimManager::iterate(GridObject* grid)
{
    iteractionCount++;
    grid->update(); // iterate

    if (iteractionCount >= maxIterations)
    {
        return 1; // max iterations reached
    }
    else if (history.hashAndCheck(grid))
    {
        return 2; // loop detected
    }
    return 0; // continue
}