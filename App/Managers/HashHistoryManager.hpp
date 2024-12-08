#ifndef HASH_HISTORY_MANAGER_H
#define HASH_HISTORY_MANAGER_H

#include <unordered_set>
#include <string>
#include <algorithm>
#include "Grid/GridObject.hpp"

class HashHistoryManager {
private:
    std::unordered_set<std::string> gridHistory;
    
    std::string createGridHash(const GridObject* grid) const;
    
    // Helper to convert CellType to string representation
    static std::string cellTypeToString(CellType type) {
        switch(type) {
            case CellType::ALIVE: return "A";
            case CellType::STATIC_DEAD: return "SD";
            case CellType::STATIC_ALIVE: return "SA";
            default: return "?";
        }
    }

public:
    bool hashAndCheck(const GridObject* grid);
    void reset();
    size_t getUniqueStatesCount() const;
};

#endif // HASH_HISTORY_MANAGER_H