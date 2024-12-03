//
// Created by oceane on 12/2/24.
//

#ifndef CELL_H
#define CELL_H
#include <iostream>
#include <vector>
#include <tuple>

class Cell
{
protected:
    std::string displayByte;
    int pos_x;
    int pos_y;

public:
    Cell();
    virtual std::vector<std::tuple<int, int>> getNeighbours();
    virtual bool switchState(int neighbourCount);
    int getPosX();
    int getPosY();
    std::string getDisplay();
    bool operator==(const Cell cell)
    {
        return this->pos_x == cell.pos_x && this->pos_y == cell.pos_y && this->displayByte == cell.displayByte;
    }
};

#endif // CELL_H
