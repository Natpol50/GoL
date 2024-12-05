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

bool SimManager::iterate(GridObject grid)
{
    map<int, int, Cell> cellmap = grid.getCellMap();
    vector < vector<int, int> neighbouringCells;
    //Getting each cell neighbourhood
    for (Cell cell : cellmap)
    {
        vector<int, int> neighbours = cell.getNeighbours();
        for (int neighbour : neighbours)
        {
            neighbouringCells.push_back(neighbour);
        }
    }
    //Counting neighbours
     std::map<<int,int>,int count > neighbourCount;
    for (vector<int, int> neighbour : neighbouringCells){
        ++neighbourCount[neighbour];
    }
    //Switching states
    for (int,int cell : neighbourCount){
        if (neighbourCount[cell] < 2 || neighbourCount[cell] > 3){
            grid.addCell(cell,CellType::ALIVECELL);
        }
        if (neighbourCount[cell] == > 3 || neighbourCount[cell] < 2){
            grid.remCell(cell);
        }
    }
    //add grid to history returns 1 if loop detected
    return history.hashAndCheck(grid);
}