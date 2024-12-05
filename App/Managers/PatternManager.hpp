#ifndef PATTERN_MANAGER_H
#define PATTERN_MANAGER_H

#include "PatternLibrary.hpp"
#include "Grid/GridObject.hpp"

class PatternManager {
private:
    const std::vector<Pattern>& patterns;
    int selectedIndex;

public:
    PatternManager();
    
    bool setSelectedIndex(int index);
    int getSelectedIndex() const;
    const Pattern* getPattern(int index) const;
    bool placePattern(GridObject* grid, int centerX, int centerY);
};

#endif // PATTERN_MANAGER_H