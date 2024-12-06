// HashHistoryManagerTest.cpp
#include <cassert>
#include <iostream>
#include "Managers/HashHistoryManager.hpp"

void runTests() {
    std::cout << "Starting HashHistoryManager tests...\n";
    
    HashHistoryManager manager;
    
    {
        std::cout << "Test 1: Empty grids...\n";
        GridObject grid1(10, 10, false);
        GridObject grid2(10, 10, false);
        
        assert(manager.hashAndCheck(&grid1) == true);
        assert(manager.hashAndCheck(&grid2) == false);
    }
    
    {
        std::cout << "Test 2: Different configurations and repeat loop...\n";
        manager.reset();
        
        GridObject grid1(10, 10, false);
        GridObject grid2(10, 10, false);
        
        grid1.addCell(1, 1, CellType::ALIVE);
        grid2.addCell(1, 2, CellType::ALIVE);
        
        assert(manager.hashAndCheck(&grid1) == true);
        assert(manager.hashAndCheck(&grid2) == true);
        assert(manager.hashAndCheck(&grid1) == false);
    }
    
    // Test 3: Different cell types
    {
        std::cout << "Test 3: Different cell types...\n";
        manager.reset();
        
        GridObject grid1(10, 10, false);
        GridObject grid2(10, 10, false);
        
        grid1.addCell(1, 1, CellType::ALIVE);
        grid2.addCell(1, 1, CellType::STATIC_ALIVE);
        
        assert(manager.hashAndCheck(&grid1) == true);  // First type
        assert(manager.hashAndCheck(&grid2) == true);  // Different type
    }
    
    // Test 4: Complex pattern with toroidal grid
    {
        std::cout << "Test 4: Complex toroidal pattern...\n";
        manager.reset();
        
        GridObject grid1(10, 10, true);  // Toroidal grid
        GridObject grid2(10, 10, true);  // Toroidal grid
        
        // Create a glider pattern in grid1
        std::vector<std::tuple<int, int, CellType>> glider = {
            {1, 1, CellType::ALIVE},
            {2, 2, CellType::ALIVE},
            {2, 3, CellType::ALIVE},
            {1, 3, CellType::ALIVE},
            {0, 3, CellType::ALIVE}
        };
        
        grid1.initialize(glider);
        grid2.initialize(glider);
        
        assert(manager.hashAndCheck(&grid1) == true);   // First pattern
        assert(manager.hashAndCheck(&grid2) == false);  // Same pattern
        
        // Add a static cell to change the pattern
        grid2.addCell(5, 5, CellType::STATIC_ALIVE);
        assert(manager.hashAndCheck(&grid2) == true);   // Modified pattern
    }
    
    // Test 5: Grid boundaries and toroidal wrapping
    {
        std::cout << "Test 5: Testing boundaries...\n";
        manager.reset();
        
        GridObject toroidal(5, 5, true);
        GridObject nonToroidal(5, 5, false);
        
        // Add cells near boundaries
        toroidal.addCell(4, 4, CellType::ALIVE);    // Corner
        toroidal.addCell(0, 4, CellType::ALIVE);    // Edge
        nonToroidal.addCell(4, 4, CellType::ALIVE); // Same positions
        nonToroidal.addCell(0, 4, CellType::ALIVE);
        
        assert(manager.hashAndCheck(&toroidal) == true);     // First grid
        assert(manager.hashAndCheck(&nonToroidal) == true);  // Different due to toroidal property
    }

    std::cout << "All tests passed!\n";
}

int main() {
    runTests();
    return 0;
}