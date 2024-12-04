// Grid.cpp
#include "Grid.hpp"

Grid::Grid(int h, int w) : height(h), width(w), isToroidal(false) {}

void Grid::initialize(std::vector<std::tuple<int, int>> positions, std::vector<CellType>& types) {
    for (size_t i = 0; i < positions.size(); ++i) {
        auto [x, y] = positions[i];
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

int Grid::countNeighbours(int x, int y) const {
    int count = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            
            int nx = x + dx;
            int ny = y + dy;
            
            if (isToroidal) {
                nx = (nx + width) % width;
                ny = (ny + height) % height;
            }
            
            if (cellmap.find({nx, ny}) != cellmap.end()) {
                count++;
            }
        }
    }
    return count;
}

void Grid::update() {
    std::map<std::pair<int, int>, bool> nextState;
    
    // Calculer états suivants
    for (auto it = cellmap.begin(); it != cellmap.end(); ++it) {
        int neighbours = countNeighbours(it->first.first, it->first.second);
        nextState[it->first] = it->second.switchState(neighbours);
    }
    
    // Mettre à jour grille
    for (const auto& state : nextState) {
        if (!state.second) {
            cellmap.erase(state.first);
        }
    }
}

bool Grid::isValidPosition(int x, int y) const {
    if (isToroidal) {
        return true;
    }
    return x >= 0 && x < width && y >= 0 && y < height;
}

Cell* Grid::getCellAt(int x, int y) {
    auto it = cellmap.find({x, y});
    if (it != cellmap.end()) {
        return &(it->second);
    }
    return nullptr;
}
