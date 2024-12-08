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
    }},
    {"Pulsar", {
        {-4, -6, CellType::ALIVE}, {-3, -6, CellType::ALIVE}, {-2, -6, CellType::ALIVE},
        {2, -6, CellType::ALIVE}, {3, -6, CellType::ALIVE}, {4, -6, CellType::ALIVE},
        
        {-4, -1, CellType::ALIVE}, {-3, -1, CellType::ALIVE}, {-2, -1, CellType::ALIVE},
        {2, -1, CellType::ALIVE}, {3, -1, CellType::ALIVE}, {4, -1, CellType::ALIVE},
        
        {-4, 1, CellType::ALIVE}, {-3, 1, CellType::ALIVE}, {-2, 1, CellType::ALIVE},
        {2, 1, CellType::ALIVE}, {3, 1, CellType::ALIVE}, {4, 1, CellType::ALIVE},
        
        {-4, 6, CellType::ALIVE}, {-3, 6, CellType::ALIVE}, {-2, 6, CellType::ALIVE},
        {2, 6, CellType::ALIVE}, {3, 6, CellType::ALIVE}, {4, 6, CellType::ALIVE},
        
        {-6, -4, CellType::ALIVE}, {-6, -3, CellType::ALIVE}, {-6, -2, CellType::ALIVE},
        {-6, 2, CellType::ALIVE}, {-6, 3, CellType::ALIVE}, {-6, 4, CellType::ALIVE},
        
        {-1, -4, CellType::ALIVE}, {-1, -3, CellType::ALIVE}, {-1, -2, CellType::ALIVE},
        {-1, 2, CellType::ALIVE}, {-1, 3, CellType::ALIVE}, {-1, 4, CellType::ALIVE},
        
        {1, -4, CellType::ALIVE}, {1, -3, CellType::ALIVE}, {1, -2, CellType::ALIVE},
        {1, 2, CellType::ALIVE}, {1, 3, CellType::ALIVE}, {1, 4, CellType::ALIVE},
        
        {6, -4, CellType::ALIVE}, {6, -3, CellType::ALIVE}, {6, -2, CellType::ALIVE},
        {6, 2, CellType::ALIVE}, {6, 3, CellType::ALIVE}, {6, 4, CellType::ALIVE}
    }}
};
#endif // PATTERN_LIBRARY_H
