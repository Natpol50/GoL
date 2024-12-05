#ifndef PATTERN_MAP_H
#define PATTERN_MAP_H

#include <string>
#include <vector>
#include "PatternCell.hpp"

struct PatternMap {
    std::string name;
    std::vector<PatternCell> cells;

    PatternMap(const std::string& n, const std::vector<PatternCell>& c) 
        : name(n), cells(c) {}
};

#endif // PATTERN_MAP_H