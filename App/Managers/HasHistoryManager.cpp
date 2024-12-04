
#include "HashHistoryManager.hpp"

HashHistoryManager::HashHistoryManager() {
    previousStates = std::unordered_set<size_t>();
}

bool HashHistoryManager::hashAndCheck(const GridObject* grid) {
    hash<GridObject> hash_output;
    size_t hash = hash_output(grid);

    if (previousStates.find(hash)) {
        return true;
    }
    
    previousStates.insert(hash);

    return false;
}

void HashHistoryManager::reset() {
    previousStates.clear();
}