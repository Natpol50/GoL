#include "GridObject.hpp"

GridObject::GridObject(int h, int w, bool toroidal) : height(h), width(w), isToroidal(toroidal) {}

void GridObject::initialize(const std::vector<std::tuple<int, int, CellType>>& cells) {
    for (const auto& cell : cells) {
        addCell(std::get<0>(cell), std::get<1>(cell), std::get<2>(cell));
    }
}

void GridObject::addCell(int x, int y, CellType type) {
    if (isToroidal) {
        x = (x + width) % width;
        y = (y + height) % height;
    }
    if (isValidPosition(x, y)) {
        auto it = cellmap.find({x, y});
        if (it != cellmap.end()) {
            if (!it->second->switchState(0)) { // Assuming 3 is the condition for switching state
                cellmap.erase(it);
            }
        } else {
            cellmap[{x, y}] = factory.createCell(x, y, type);
            // std::cout << "Added cell at " << x << ", " << y << std::endl;
        }
    }
}

void GridObject::update() {
    // std::cout << "Updating grid" << std::endl;
    
    // Count live neighbors
    std::map<std::tuple<int, int>, int> positionCounts;
    for (const auto& [pos, cell] : cellmap) {
        auto neighbours = cell->getNeighbours();
        for (auto neighPos : neighbours) {
            int x = std::get<0>(neighPos);
            int y = std::get<1>(neighPos);

            if (isToroidal) {
                x = (x + width) % width;
                y = (y + height) % height;
                neighPos = std::make_tuple(x, y);
                positionCounts[neighPos]++;
            } else if (isValidPosition(x, y)) {
                positionCounts[neighPos]++;
            }
        }
    }


    // Process cell births, processing birth before deaths to avoid conflicts if the default born cell dies with the same condition as it can birth at.
    for (const auto& [pos, count] : positionCounts) {
        if (count == 3) {
            int x = std::get<0>(pos);
            int y = std::get<1>(pos);
            if (cellmap.find({x, y}) == cellmap.end() && isValidPosition(x, y)) {
                addCell(x, y, CellType::ALIVE);
            }
        }
    }

    // Process cell deaths
    auto it = cellmap.begin();
    while (it != cellmap.end()) {
        std::tuple<int, int> pos = {it->first.first, it->first.second};
        if (!it->second->switchState(positionCounts[pos])) {
            // std::cout << "Removing cell at " << it->first.first << ", " << it->first.second << std::endl;
            it = cellmap.erase(it);
        } else {
            ++it;
        }
    }
}

bool GridObject::isValidPosition(int x, int y) const {
    if (isToroidal) return true;
    return x >= 0 && x < width && y >= 0 && y < height;
}

const Cell* GridObject::getCellAt(int x, int y) const {
    auto it = cellmap.find({x, y});
    return it != cellmap.end() ? it->second.get() : nullptr;
}


void GridObject::print() const {
    std::cout << "Grid IsToroidal : " << isToroidal << std::endl;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            auto it = cellmap.find({x, y});
            if (it == cellmap.end()) {
                std::cout << "0 ";
            } else {
                switch(it->second->getDisplay()) {
                    case CellType::ALIVE: std::cout << "1 "; break;
                    case CellType::STATIC_DEAD: std::cout << "2 "; break;
                    case CellType::STATIC_ALIVE: std::cout << "3 "; break;
                    default: std::cout << "0 ";
                }
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}