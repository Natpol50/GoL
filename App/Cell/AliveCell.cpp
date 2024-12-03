//
// Created by oceane on 12/2/24.
//

#include "AliveCell.hpp"
using namespace std;

AliveCell::AliveCell() : displayByte("1"), pos_x(0), pos_y(0) {}
AliveCell::AliveCell(const int x, const int y) : displayByte("1"), pos_x(x), pos_y(y) {}

bool AliveCell::switchState(const int neighbourCount)
{
    /* Returns 0 if cell dead, 1 if alive */
    if (neighbourCount < 2 || neighbourCount > 3)
    {
        return false;
    }
    return true;
}
