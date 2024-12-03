//
// Created by oceane on 12/2/24.
//

#include "AliveStaticC.hpp"

AliveStaticC::AliveStaticC() : pos_x(0), pos_y(0), displayByte("1") {}
AliveStaticC::AliveStaticC(int x, int y) : pos_x(x), pos_y(y), displayByte("1") {}

bool AliveStaticC::switchState(int neighbourCount)
{
    // A static cell doesn't change state
    return 1;
}