#include "Cell.hpp"

Cell::Cell(int x, int y) : pos_x(x), pos_y(y) {}

std::vector<std::tuple<int, int>> Cell::getNeighbours() const {
    std::vector<std::tuple<int, int>> neighbours;
    neighbours.emplace_back(pos_x - 1, pos_y + 1);
    neighbours.emplace_back(pos_x, pos_y + 1);
    neighbours.emplace_back(pos_x + 1, pos_y + 1);
    neighbours.emplace_back(pos_x - 1, pos_y);
    neighbours.emplace_back(pos_x + 1, pos_y);
    neighbours.emplace_back(pos_x - 1, pos_y - 1);
    neighbours.emplace_back(pos_x, pos_y - 1);
    neighbours.emplace_back(pos_x + 1, pos_y - 1);
    return neighbours;
}