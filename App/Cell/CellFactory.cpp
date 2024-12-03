//
// Created by oceane on 12/3/24.
//

#include "CellFactory.h"

bool CellFactory::createCell(int x, int y, CellType cellType) {
     switch (cellType) {
        case CellType::ALIVE:
          return true;
        case CellType::STATIC_ALIVE:
          return true;
        case CellType::STATIC_DEAD:
          return true;
        defalt:
          return false;
     }
}