#ifndef ALIVECELL_H
#define ALIVECELL_H

#include "Cell.hpp"

class AliveCell : public Cell {
public:
    AliveCell(int x, int y);
    bool switchState(int neighbourCount) const override;
};

#endif // ALIVECELL_H