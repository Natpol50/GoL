//
// Created by oceane on 12/3/24.
//

#include "CellFactory.hpp"

Cell CellFactory::createCell(const int x, const int y, const CellType cellType)
{
  switch (cellType)
  {
  case CellType::ALIVE:
    return AliveCell(x, y);
  case CellType::STATIC_ALIVE:
    return AliveStaticC(x, y);
  case CellType::STATIC_DEAD:
    return DeadStaticC(x, y);
  default:
    return AliveCell();
  }
}
