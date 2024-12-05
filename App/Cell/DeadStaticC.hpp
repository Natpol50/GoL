#ifndef DEADSTATICC_H
#define DEADSTATICC_H

#include "Cell.hpp"

class DeadStaticC : public Cell {
public:
    DeadStaticC(int x, int y);
    bool switchState(int neighbourCount) const override;
    std::vector<std::tuple<int, int>> getNeighbours() const override;
};

#endif // DEADSTATICC_H
