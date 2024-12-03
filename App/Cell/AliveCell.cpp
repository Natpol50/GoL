//
// Created by oceane on 12/2/24.
//

#include "AliveCell.hpp"
using namespace std;

AliveCell::AliveCell() : pos_x(0), pos_y(0), displayByte("1") {}
AliveCell::AliveCell(int x, int y) : pos_x(x), pos_y(y), displayByte("1") {}

bool AliveCell::switchState(int neighbourCount)
{
    /* Returns 0 if cell dead, 1 if alive */
    if (neighbourCount < 2 || neighbourCount > 3)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
