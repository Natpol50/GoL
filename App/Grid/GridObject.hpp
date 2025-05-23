#ifndef GRID_H
#define GRID_H

#include <map>
#include <string>
#include "Cell/CellFactory.hpp"
#include <memory>

class GridObject {
private:
    int height;
    int width;
    std::map<std::pair<int, int>, std::unique_ptr<Cell>> cellmap;
    bool isToroidal;
    CellFactory factory;

public:
    GridObject();
    GridObject(int height, int width, bool toroidal = false);
    
    void initialize(const std::vector<std::tuple<int, int, CellType>>& cells);
    void addCell(int x, int y, CellType type);
    bool removeCell(int x, int y);
    void update();
    bool isValidPosition(int x, int y) const;
    const Cell* getCellAt(int x, int y) const;
    void print() const;

    friend class FileManager;
    friend class HashHistoryManager;
    friend class SFMLManager;
};

#endif // GRID_H