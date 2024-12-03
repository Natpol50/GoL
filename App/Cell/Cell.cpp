//
// Created by oceane on 12/2/24.
//

#include "Cell.hpp"
Cell::Cell(): displayByte(" "), pos_x(0), pos_y(0)
{

}

int Cell::getPosX() const
{
    return pos_x;
}

int Cell::getPosY() const
{
    return pos_y;
}

std::string Cell::getDisplay()
{
    return displayByte;
}

std::vector<std::tuple<int, int>> Cell::getNeighbours()
{
    std::vector<std::tuple<int, int>> neighbours;
    neighbours.emplace_back(pos_x - 1, pos_y + 1);
    neighbours.emplace_back(pos_x, pos_y + 1);
    neighbours.emplace_back(pos_x + 1, pos_y + 1);
    neighbours.emplace_back(pos_x - 1, pos_y);
    neighbours.emplace_back(pos_x + 1, pos_y);
    neighbours.emplace_back(pos_x - 1, pos_y - 1);
    neighbours.emplace_back(pos_x, pos_y - 1);
    neighbours.emplace_back(pos_x + 1, pos_y - 1);
    neighbours.emplace_back(pos_x + 1, pos_y - 1);
    return neighbours;
}

bool Cell::switchState(int neighbourCount)
{
    return false;
}