//
// Created by oceane on 12/2/24.
//

#ifndef ALIVESTATICC_H
#define ALIVESTATICC_H

#include "Cell.hpp"

class AliveStaticC : public Cell
{
private:
  std::string displayByte;
  int pos_x;
  int pos_y;

public:
  AliveStaticC();
  AliveStaticC(int x, int y);
  std::vector<std::tuple<int, int>> getNeighbours();
  bool switchState(int neighbourCount);
};

#endif // ALIVESTATICC_H
