#ifndef CELLFACTORY_H
#define CELLFACTORY_H
#include <iostream>
#include <memory>
#include "Cell.hpp"
#include "AliveCell.hpp"
#include "DeadStaticC.hpp"
#include "AliveStaticC.hpp"


class CellFactory {
public:
    static std::unique_ptr<Cell> createCell(int x, int y, CellType type);
};

#endif // CELLFACTORY_H