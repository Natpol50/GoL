//
// Created by oceane on 12/2/24.
//

#include "AliveStaticC.hpp"

AliveStaticC::AliveStaticC() : displayByte(CellType::STATIC_ALIVE), pos_x(0), pos_y(0) {}
AliveStaticC::AliveStaticC(const int x, const int y) : displayByte(CellType::STATIC_ALIVE), pos_x(x), pos_y(y) {}

bool AliveStaticC::switchState(int neighbourCount)
{
    // A static cell doesn't change state
    return true;
}