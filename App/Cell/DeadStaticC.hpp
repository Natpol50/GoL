//
// Created by oceane on 12/2/24.
//

#ifndef DEADSTATICC_H
#define DEADSTATICC_H

#include "Cell.hpp"

class DeadStaticC : public Cell
{
private:
    int pos_x;
    int pos_y;
    CellType displayByte;

public:
    DeadStaticC();
    DeadStaticC(int x, int y);
    std::vector<std::tuple<int, int>> getNeighbours() const override;
    bool switchState(int neighbourCount) const override;
};

#endif // DEADSTATICC_H
