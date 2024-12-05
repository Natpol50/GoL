#ifndef PATTERN_CELL_H
#define PATTERN_CELL_H

#include "CellType.hpp"

struct PatternCell {
    int posX;
    int posY;
    CellType type;

    PatternCell(int x, int y, CellType t) : posX(x), posY(y), type(t) {}
};

#endif // PATTERN_CELL_H