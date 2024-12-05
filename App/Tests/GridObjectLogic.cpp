#include <iostream>
#include "Grid/GridObject.hpp"

void testInitialize() {
    GridObject grid(10, 10);
    std::vector<std::tuple<int, int, CellType>> cells = {
        {1, 1, CellType::ALIVE}, 
        {1, 2, CellType::ALIVE}, 
        {1, 3, CellType::ALIVE}, 
        {2, 2, CellType::ALIVE}
    };
    
    grid.initialize(cells);
    
    std::cout << "Test Initialize: "
              << ((grid.getCellAt(1, 1) && grid.getCellAt(1, 2) && grid.getCellAt(1, 3) && grid.getCellAt(2, 2)) ? "PASS" : "FAIL")
              << std::endl;
    //grid.print();
}

void testUpdate() {
    GridObject grid(10, 10);
    grid.addCell(1, 1, CellType::ALIVE);
    grid.addCell(1, 2, CellType::ALIVE);
    grid.addCell(1, 3, CellType::ALIVE);
    
    //grid.print();
    
    grid.update();
    
    //grid.print();
    
    
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
    GridObject grid(10, 10);
    //grid.print();
    grid.addCell(1, 1, CellType::STATIC_ALIVE);
    grid.update();
    
    //grid.print();
    
    std::cout << "Test Static Cell: " 
              << (grid.getCellAt(1, 1) ? "PASS" : "FAIL") 
              << std::endl;
    //grid.print();
}

int main() {
    std::cout << "Starting GridObject Tests\n-------------------" << std::endl;
    testInitialize();
    testUpdate();
    testStaticCell();
    std::cout << "-------------------\nTests Complete" << std::endl;
    return 0;
}
