#include "PatternManager.hpp"

std::map<std::string, PatternMap> PatternManager::patterns;

int PatternManager::SetIndexInit(const std::string& name, int& errors) {
    auto it = patterns.find(name);
    if (it != patterns.end()) {
        return std::distance(patterns.begin(), it);
    }
    errors++;
    return -1;
}

PatternMap PatternManager::GetIndex(int index) {
    auto it = patterns.begin();
    std::advance(it, index);
    return it->second;
}

std::vector<PatternMap> PatternManager::GetPattern() {
    std::vector<PatternMap> result;
    for (const auto& [name, pattern] : patterns) {
        result.push_back(pattern);
    }
    return result;
}

bool PatternManager::PlacePattern(int x, int y, bool success, GridObject& grid, const PatternMap& pattern) {
    if (!canPlacePattern(grid, pattern, x, y)) {
        return false;
    }

    for (const auto& cell : pattern.cells) {
        auto [absX, absY] = translateCoordinates(x, y, cell.posX, cell.posY);
        grid.addCell(absX, absY, cell.type);
    }
    return true;
}

void PatternManager::addPattern(const std::string& name, const std::vector<PatternCell>& cells) {
    patterns.emplace(name, PatternMap(name, cells));
}

const PatternMap* PatternManager::getPattern(const std::string& name) {
    auto it = patterns.find(name);
    return it != patterns.end() ? &it->second : nullptr;
}

std::vector<std::string> PatternManager::getPatternNames() {
    std::vector<std::string> names;
    for (const auto& [name, _] : patterns) {
        names.push_back(name);
    }
    return names;
}

bool PatternManager::canPlacePattern(const GridObject& grid, const PatternMap& pattern, int x, int y) {
    for (const auto& cell : pattern.cells) {
        auto [absX, absY] = translateCoordinates(x, y, cell.posX, cell.posY);
        if (!grid.isValidPosition(absX, absY)) {
            return false;
        }
    }
    return true;
}

std::pair<int, int> PatternManager::translateCoordinates(int baseX, int baseY, int patternX, int patternY) {
    return {baseX + patternX, baseY + patternY};
}