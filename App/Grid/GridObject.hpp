// Grid.hpp



#ifndef GRID_H
#define GRID_H

#include <map>
#include <string>
#include "Cell/Cell.hpp"
#include "Cell/CellFactory.hpp"
#include <memory>

class GridObject {
private:
    int height;
    int width;
    std::map<std::pair<int, int>, std::unique_ptr<Cell>> cellmap;
    bool isToroidal;
    CellFactory factory;

public:
    GridObject(int height, int width);
    
    void initialize(const std::vector<std::tuple<int, int>>& positions, 
                   const std::vector<CellType>& types);
    void addCell(int x, int y, CellType type);
    bool removeCell(int x, int y);
    void update();
    bool isValidPosition(int x, int y) const;
    const Cell* getCellAt(int x, int y) const;
    void print() const;
};

#endif // GRID_H