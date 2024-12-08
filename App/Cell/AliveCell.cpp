#include "AliveCell.hpp"

AliveCell::AliveCell(int x, int y) : Cell(x, y) {
    displayByte = CellType::ALIVE;
}

bool AliveCell::switchState(int neighbourCount) const {
    return neighbourCount == 2 || neighbourCount == 3;
}
