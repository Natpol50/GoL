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

int SimManager::iterate(GridObject grid)
{
    iteractionCount++;
    grid.update(); // iterate

    // add grid to history returns 1 if loop detected
    return history.hashAndCheck(grid);
}