//
// Created by oceane on 12/3/24.
//

#ifndef CELLFACTORY_H
#define CELLFACTORY_H
#include <iostream>
#include "CellType.hpp"
#include "Cell.hpp"

class CellFactory
{
public:
  static Cell createCell(int x, int y, CellType cellType);
};

#endif // CELLFACTORY_H
