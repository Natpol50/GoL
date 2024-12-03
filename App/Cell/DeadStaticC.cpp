//
// Created by oceane on 12/2/24.
//

#include "DeadStaticC.hpp"

DeadStaticC::DeadStaticC() : pos_x(0), pos_y(0), displayByte("2") {}
DeadStaticC::DeadStaticC(int x, int y) : pos_x(x), pos_y(y), displayByte("2") {}

bool DeadStaticC::switchState(int neighbourCount)
{
    // Never changes state
    return 1;
}

std::vector<std::tuple<int, int>> Cell::getNeighbours()
{
    std::vector<std::tuple<int, int>> neighbours;
    return neighbours;
}
