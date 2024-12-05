#include "AliveStaticC.hpp"

AliveStaticC::AliveStaticC(int x, int y) : Cell(x, y) {
    displayByte = CellType::STATIC_ALIVE;
}

bool AliveStaticC::switchState(int neighbourCount) const {
    return true;  // Never dies
}