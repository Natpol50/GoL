

#ifndef SIM_MANAGER_HPP
#define SIM_MANAGER_HPP

#include "HashHistoryManager.hpp"
#include "FileManager.hpp"
#include "Grid/GridObject.hpp"

class SimManager
{
private:
    HashHistoryManager history;
    int maxIterations;
    int iteractionCount;
public:
    SimManager();
    SimManager(int maxIterations);
    int getCurrentIterationCount();
    int iterate(GridObject* grid, FileManager* FileMan, bool Save);
};

#endif //SIM_MANAGER_HPP