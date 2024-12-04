// Grid.hpp

#include <map>
#include <vector>
#include <string>
#include "Cell/Cell.hpp"
#include "Cell/CellFactory.hpp"

class Grid {
private:
    int height;
    int width;
    std::map<std::pair<int, int>, Cell> cellmap;
    bool isToroidal;
    CellFactory factory;

public:
    Grid(int height, int width);
    
    void initialize(std::vector<std::tuple<int, int>>, std::vector<CellType>&);
    
    void addCell(int x, int y, CellType cellType);
    
    bool removeCell(int x, int y);
    
    void update();
    
    bool isValidPosition(int x, int y) const;
    
    Cell* getCellAt(int x, int y);
    
    void print() const;
};
