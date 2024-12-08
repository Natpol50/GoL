#include "HashHistoryManager.hpp"
#include <sstream>
#include <algorithm>

std::string HashHistoryManager::createGridHash(const GridObject* grid) const {
    std::stringstream hashStream;
    
    hashStream << grid->width << "x" << grid->height << "t" << grid->isToroidal;
    
    std::vector<std::pair<std::pair<int, int>, CellType>> sortedCells;
    
    for (const auto& [pos, cell] : grid->cellmap) {
        sortedCells.push_back({pos, cell->getDisplay()});
    }
    
    std::sort(sortedCells.begin(), sortedCells.end());
    for (const auto& [pos, type] : sortedCells) {
        hashStream << "(" << pos.first << "," << pos.second << "):"
                  << cellTypeToString(type);
    }
    
    return hashStream.str();
}

bool HashHistoryManager::hashAndCheck(const GridObject* grid) {
    std::string hash = createGridHash(grid);
    return gridHistory.insert(hash).second;
}

void HashHistoryManager::reset() {
    gridHistory.clear();
}

size_t HashHistoryManager::getUniqueStatesCount() const {
    return gridHistory.size();
}

