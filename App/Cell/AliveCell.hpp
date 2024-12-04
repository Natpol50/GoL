//
// Created by oceane on 12/2/24.
//

#ifndef ALIVECELL_H
#define ALIVECELL_H
#include "Cell.hpp"
#include <iostream>

class AliveCell : public Cell
{
private:
  CellType displayByte;
  int pos_x;
  int pos_y;

public:
  AliveCell();
  AliveCell(int x, int y);
  bool switchState(int neighbourCount) const override;
};

#endif // ALIVECELL_H
