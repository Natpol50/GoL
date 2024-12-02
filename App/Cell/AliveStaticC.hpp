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
  bool switchState(int neighbourCount) override;
};

#endif // ALIVESTATICC_H
