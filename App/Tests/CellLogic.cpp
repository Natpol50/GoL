

#include <iostream>
#include <cassert>
#include "Cell/CellFactory.hpp"



void assertTrue(bool condition, const std::string& testName) {
    if (condition) {
        std::cout << "✓ " << testName << " PASSED" << std::endl;
    } else {
        std::cout << "✗ " << testName << " FAILED" << std::endl;
    }
}


void testAliveCell() {
    std::cout << "\nTesting AliveCell..." << std::endl;
    

    AliveCell cell(5, 7);
    assertTrue(cell.getPosX() == 5, "AliveCell position X");
    assertTrue(cell.getPosY() == 7, "AliveCell position Y");
    assertTrue(cell.getDisplay() == CellType::ALIVE, "AliveCell display type");


    auto neighbours = cell.getNeighbours();
    assertTrue(neighbours.size() == 8, "AliveCell number of neighbours");


    assertTrue(cell.switchState(2), "AliveCell survives with 2 neighbours");
    assertTrue(cell.switchState(3), "AliveCell survives with 3 neighbours");
    assertTrue(!cell.switchState(1), "AliveCell dies with 1 neighbour");
    assertTrue(!cell.switchState(4), "AliveCell dies with 4 neighbours");
    assertTrue(!cell.switchState(0), "AliveCell dies with 0 neighbours");
}


void testDeadStaticC() {
    std::cout << "\nTesting DeadStaticC..." << std::endl;
    
    DeadStaticC cell(3, 4);
    assertTrue(cell.getPosX() == 3, "DeadStaticC position X");
    assertTrue(cell.getPosY() == 4, "DeadStaticC position Y");
    assertTrue(cell.getDisplay() == CellType::STATIC_DEAD, "DeadStaticC display type");


    auto neighbours = cell.getNeighbours();
    assertTrue(neighbours.empty(), "DeadStaticC has no neighbours");


    assertTrue(cell.switchState(0), "DeadStaticC stays dead with 0 neighbours");
    assertTrue(cell.switchState(3), "DeadStaticC stays dead with 3 neighbours");
    assertTrue(cell.switchState(8), "DeadStaticC stays dead with 8 neighbours");
}


void testAliveStaticC() {
    std::cout << "\nTesting AliveStaticC..." << std::endl;
    
    AliveStaticC cell(1, 2);
    assertTrue(cell.getPosX() == 1, "AliveStaticC position X");
    assertTrue(cell.getPosY() == 2, "AliveStaticC position Y");
    assertTrue(cell.getDisplay() == CellType::STATIC_ALIVE, "AliveStaticC display type");


    assertTrue(cell.switchState(0), "AliveStaticC stays alive with 0 neighbours");
    assertTrue(cell.switchState(3), "AliveStaticC stays alive with 3 neighbours");
    assertTrue(cell.switchState(8), "AliveStaticC stays alive with 8 neighbours");
}


void testCellFactory() {
    std::cout << "\nTesting CellFactory..." << std::endl;
    
    auto aliveCell = CellFactory::createCell(1, 1, CellType::ALIVE);
    assertTrue(aliveCell->getDisplay() == CellType::ALIVE, "Factory creates AliveCell");
    
    auto staticAliveCell = CellFactory::createCell(2, 2, CellType::STATIC_ALIVE);
    assertTrue(staticAliveCell->getDisplay() == CellType::STATIC_ALIVE, "Factory creates AliveStaticC");
    
    auto staticDeadCell = CellFactory::createCell(3, 3, CellType::STATIC_DEAD);
    assertTrue(staticDeadCell->getDisplay() == CellType::STATIC_DEAD, "Factory creates DeadStaticC");
}


void testCellInteractions() {
    std::cout << "\nTesting Cell Interactions..." << std::endl;
    

    AliveCell centerCell(5, 5);
    auto neighbours = centerCell.getNeighbours();
    

    std::vector<std::tuple<int, int>> expectedNeighbours = {
        {4, 6}, {5, 6}, {6, 6}, 
        {4, 5}, {6, 5},         
        {4, 4}, {5, 4}, {6, 4}
    };
    
    assertTrue(neighbours == expectedNeighbours, "Neighbour positions are correct");
}

int main() {
    std::cout << "Starting Cell Tests\n==================" << std::endl;
    
    testAliveCell();
    testDeadStaticC();
    testAliveStaticC();
    testCellFactory();
    testCellInteractions();
    
    std::cout << "\n==================\nTests Complete" << std::endl;
    return 0;
}