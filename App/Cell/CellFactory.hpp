//
// Created by oceane on 12/3/24.
//

#ifndef CELLFACTORY_H
#define CELLFACTORY_H
#include <iostream>
#include "CellType.hpp"
#include "Cell.hpp"
#include "AliveCell.hpp"
#include "DeadStaticC.hpp"
#include "AliveStaticC.hpp"

class CellFactory
{
public:
  Cell createCell(int x, int y, CellType cellType);
};

#endif // CELLFACTORY_H
