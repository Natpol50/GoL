#ifndef PATTERN_LIBRARY_H
#define PATTERN_LIBRARY_H

#include <vector>
#include <tuple>
#include "Cell/CellType.hpp"

struct Pattern {
    std::string name;
    std::vector<std::tuple<int, int, CellType>> cells;
};

const std::vector<Pattern> PATTERN_LIBRARY = {
    {"Crawler", {
        {-1, -1, CellType::ALIVE},
        {0, -1, CellType::ALIVE},
        {1, -1, CellType::ALIVE},
        {1, 0, CellType::ALIVE},
        {0, 1, CellType::ALIVE}
    }},
    {"Blinker", {
        {-1, 0, CellType::ALIVE},
        {0, 0, CellType::ALIVE},
        {1, 0, CellType::ALIVE}
    }},
    {"Block", {
        {-1, -1, CellType::ALIVE},
        {0, -1, CellType::ALIVE},
        {-1, 0, CellType::ALIVE},
        {0, 0, CellType::ALIVE}
    }}
    // You can add other patterns here
};

#endif // PATTERN_LIBRARY_H