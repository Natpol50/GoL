

#ifndef SIM_MANAGER_HPP
#define SIM_MANAGER_HPP

#include "HashHistoryManager.hpp"
#include "GridObject.hpp"

class SimManager
{
private:
    HashHistoryManager history;
    int maxIterations;
    int iteractionCount;
public:
    SimManager(int maxIterations);
    int getCurrentIterationCount();
    bool iterate(GridObject grid);
};

#endif //SIM_MANAGER_HPP