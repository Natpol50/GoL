#ifndef PATTERN_MANAGER_H
#define PATTERN_MANAGER_H

#include <string>
#include <vector>
#include <map>
#include "PatternMap.hpp"
#include "GridObject.hpp"

class PatternManager {
private:
    static std::map<std::string, PatternMap> patterns;
    
public:
    static int SetIndexInit(const std::string& name, int& errors);
    

    static PatternMap GetIndex(int index);
    

    static std::vector<PatternMap> GetPattern();
    

    static bool PlacePattern(int x, int y, bool success, GridObject& grid, const PatternMap& pattern);


    static void addPattern(const std::string& name, const std::vector<PatternCell>& cells);
    static const PatternMap* getPattern(const std::string& name);
    static std::vector<std::string> getPatternNames();
};

#endif // PATTERN_MANAGER_H