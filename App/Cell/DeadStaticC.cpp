#include "DeadStaticC.hpp"

DeadStaticC::DeadStaticC(int x, int y) : Cell(x, y) {
    displayByte = CellType::STATIC_DEAD;
}

bool DeadStaticC::switchState(int neighbourCount) const {
    return true;  // Never dies
}

std::vector<std::tuple<int, int>> DeadStaticC::getNeighbours() const {
    return {};  // Don't act on anything
}