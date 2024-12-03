//
// Created by oceane on 12/2/24.
//

#include "Cell.hpp"

int Cell::getPosX()
{
    return pos_x;
}

int Cell::getPosY()
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
    neighbours.push_back(std::make_tuple(pos_x - 1, pos_y + 1));
    neighbours.push_back(std::make_tuple(pos_x, pos_y + 1));
    neighbours.push_back(std::make_tuple(pos_x + 1, pos_y + 1));
    neighbours.push_back(std::make_tuple(pos_x - 1, pos_y));
    neighbours.push_back(std::make_tuple(pos_x + 1, pos_y));
    neighbours.push_back(std::make_tuple(pos_x - 1, pos_y - 1));
    neighbours.push_back(std::make_tuple(pos_x, pos_y - 1));
    neighbours.push_back(std::make_tuple(pos_x + 1, pos_y - 1));
    neighbours.push_back(std::make_tuple(pos_x + 1, pos_y - 1));
    return neighbours;
}
