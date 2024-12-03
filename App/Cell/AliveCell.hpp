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
  std::string displayByte;
  int pos_x;
  int pos_y;

public:
  AliveCell();
  AliveCell(int x, int y);
  std::vector<std::tuple<int, int>> getNeighbours();
  bool switchState(int neighbourCount);
};

#endif // ALIVECELL_H
