// Grid.cpp
#include "Grid.hpp"

Grid::Grid(int h, int w) : height(h), width(w), isToroidal(false) {}

void Grid::initialize(std::vector<std::tuple<int, int>> positions, std::vector<CellType>& types) {
    for (size_t i = 0; i < positions.size(); ++i) {
        int x = std::get<0>(positions[i]);
        int y = std::get<1>(positions[i]);
        addCell(x, y, types[i]);
    }
}

void Grid::addCell(int x, int y, CellType cellType) {
    if (isValidPosition(x, y)) {
        cellmap[{x, y}] = factory.createCell(x, y, cellType);
    }
}

bool Grid::removeCell(int x, int y) {
    if (cellmap.find({x, y}) != cellmap.end()) {
        cellmap.erase({x, y});
        return true;
    }
    return false;
}

void Grid::update() {
    std::map<std::tuple<int, int>, int> positionCounts;


    for (const auto& it : cellmap) {
        std::vector<std::tuple<int, int>> neighbours = it.second.getNeighbours();
        for (const auto& pos : neighbours) {
            positionCounts[pos]++;
        }
    }


    std::map<std::pair<int, int>, Cell> newGrid;
    for (const auto& it : cellmap) {
        std::tuple<int, int> pos = std::make_tuple(it.first.first, it.first.second);
        if (it.second.switchState(positionCounts[pos])) {
            newGrid[it.first] = it.second;
        }
    }


    for (const auto& it : positionCounts) {
        if (it.second == 3) {
            int x = std::get<0>(it.first);
            int y = std::get<1>(it.first);
            if (cellmap.find({x, y}) == cellmap.end() && isValidPosition(x, y)) {
                newGrid[{x, y}] = factory.createCell(x, y, CellType::ALIVE);
            }
        }
    }

    cellmap = std::move(newGrid);
}

bool Grid::isValidPosition(int x, int y) const {
    if (isToroidal) {
        return true;
    }
    return x >= 0 && x < width && y >= 0 && y < height;
}

Cell* Grid::getCellAt(int x, int y) {  // For test purposes
    auto it = cellmap.find({x, y});
    if (it != cellmap.end()) {
        return &(it->second);
    }
    return nullptr;
}

void Grid::print() const {   // For test purposes
   for (int y = 0; y < height; y++) {
       for (int x = 0; x < width; x++) {
           auto it = cellmap.find({x, y});
           if (it == cellmap.end()) {
               std::cout << "0 ";
           } else {
               switch(it->second.getDisplay()) {
                   case CellType::ALIVE: std::cout << "1 "; break;
                   case CellType::STATIC_ALIVE: std::cout << "2 "; break;
                   case CellType::STATIC_DEAD: std::cout << "3 "; break;
                   default: std::cout << "0 ";
               }
           }
       }
       std::cout << std::endl;
   }
   std::cout << std::endl;
}
