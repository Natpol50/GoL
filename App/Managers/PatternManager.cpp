#include "PatternManager.hpp"

PatternManager::PatternManager() 
    : patterns(PATTERN_LIBRARY), selectedIndex(-1) {}

bool PatternManager::setSelectedIndex(int index) {
    if (index >= 0 && index < patterns.size()) {
        selectedIndex = index;
        return true;
    }
    return false;
}

int PatternManager::getSelectedIndex() const {
    return selectedIndex;
}

const Pattern* PatternManager::getPattern(int index) const {
    if (index >= 0 && index < patterns.size()) {
        return &patterns[index];
    }
    return nullptr;
}

bool PatternManager::placePattern(GridObject* grid, int centerX, int centerY) {
    if (!grid || selectedIndex < 0 || selectedIndex >= patterns.size()) {
        return false;
    }

    const Pattern& pattern = patterns[selectedIndex];
    for (const auto& [relX, relY, type] : pattern.cells) {
        grid->addCell(centerX + relX, centerY + relY, type);
    }
    return true;
}
