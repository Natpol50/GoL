#include <iostream>
#include "Grid.hpp"

void testInitialize() {
    Grid grid(10, 10);
    std::vector<std::tuple<int, int>> positions = {{1, 1}, {1, 2}, {1, 3}, {2,2}};
    std::vector<CellType> types = {CellType::ALIVE, CellType::ALIVE, CellType::ALIVE};
    
    grid.initialize(positions, types);
    
    std::cout << "Test Initialize: "
              << ((grid.getCellAt(1, 1) && grid.getCellAt(1, 2) && grid.getCellAt(1, 3)) ? "PASS" : "FAIL")
              << std::endl;
    grid.print();
}

void testUpdate() {
    Grid grid(10, 10);
    grid.addCell(1, 1, CellType::ALIVE);
    grid.addCell(1, 2, CellType::ALIVE);
    grid.addCell(1, 3, CellType::ALIVE);
    
    grid.print();
    
    grid.update();
    
    grid.print();
    
    
    bool updateCorrect = grid.getCellAt(0, 2) && 
                        grid.getCellAt(1, 2) && 
                        grid.getCellAt(2, 2) &&
                        !grid.getCellAt(1, 1) && 
                        !grid.getCellAt(1, 3);
                        
    std::cout << "Test Update: " 
              << (updateCorrect ? "PASS" : "FAIL") 
              << std::endl;
}

void testStaticCell() {
    Grid grid(10, 10);
    grid.print();
    grid.addCell(1, 1, CellType::STATIC_ALIVE);
    grid.update();
    
    grid.print();
    
    std::cout << "Test Static Cell: " 
              << (grid.getCellAt(1, 1) ? "PASS" : "FAIL") 
              << std::endl;
    grid.print();
}

int main() {
    std::cout << "Starting Grid Tests\n-------------------" << std::endl;
    testInitialize();
    testUpdate();
    testStaticCell();
    std::cout << "-------------------\nTests Complete" << std::endl;
    return 0;
}
