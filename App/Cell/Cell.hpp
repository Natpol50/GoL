#ifndef CELL_H
#define CELL_H

#include <vector>
#include <tuple>
#include "CellType.hpp"

class Cell {
protected:
    CellType displayByte;
    int pos_x;
    int pos_y;

public:
    Cell(int x, int y);
    virtual ~Cell() = default;
    
    virtual std::vector<std::tuple<int, int>> getNeighbours() const;
    virtual bool switchState(int neighbourCount) const = 0;
    
    int getPosX() const { return pos_x; }
    int getPosY() const { return pos_y; }
    CellType getDisplay() const { return displayByte; }
};

#endif // CELL_H