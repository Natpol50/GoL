#ifndef ALIVESTATICC_H
#define ALIVESTATICC_H

#include "Cell.hpp"
class AliveStaticC : public Cell {
public:
    AliveStaticC(int x, int y);
    bool switchState(int neighbourCount) const override;
};

#endif // ALIVESTATICC_H