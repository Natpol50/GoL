//
// Created by oceane on 12/3/24.
//

#ifndef CELLTYPE_H
#define CELLTYPE_H

#include <iostream>
#include "AliveCell.hpp"
#include "DeadStaticC.hpp"
#include "AliveStaticC.hpp"

enum class CellType
{
    ALIVE,
    STATIC_DEAD,
    STATIC_ALIVE,
};

#endif // CELLTYPE_H
