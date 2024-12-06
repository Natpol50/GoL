#include <cassert>
#include <iostream>
#include "Managers/SimManager.hpp"


void runTests() {
    std::cout << "Starting SimManager tests...\n";
    
    {
        std::cout << "Test 1: Basic iteration counting...\n";
        GridObject grid(10, 10, false);
        FileManager fileMan("test_input.txt", "output");
        SimManager sim(5);
        
        assert(sim.getCurrentIterationCount() == 0);
        int result = sim.iterate(&grid, &fileMan, false, false);
        assert(sim.getCurrentIterationCount() == 1);
        assert(result == 0);
    }
    
    {
        std::cout << "Test 2: Max iterations limit...\n";
        GridObject grid(10, 10, false);
        FileManager fileMan("test_input.txt", "output");
        SimManager sim(2);
        
        assert(sim.iterate(&grid, &fileMan, false, false) == 0);
        assert(sim.iterate(&grid, &fileMan, false, false) == 1);
    }
    
    {
        std::cout << "Test 3: Hash detection...\n";
        GridObject grid(10, 10, false);
        FileManager fileMan("test_input.txt", "output");
        SimManager sim(100);
        
        grid.addCell(1, 1, CellType::ALIVE);
        grid.addCell(1, 2, CellType::ALIVE);
        grid.addCell(2, 1, CellType::ALIVE);
        grid.addCell(2, 2, CellType::ALIVE);
        
        int result = sim.iterate(&grid, &fileMan, false, true);
        assert(result == 0);
        
        result = sim.iterate(&grid, &fileMan, false, true);
        assert(result == 2);
    }
    
    {
        std::cout << "Test 4: File saving + max iteration...\n";
        FileManager fileMan("test_input.txt", "output");
        GridObject grid = fileMan.LoadInitialState();
        SimManager sim(3);
        
        
        while (sim.iterate(&grid, &fileMan, true, false) == 0) {
            true;
        }
        
    }
    
    {
        std::cout << "Test 5: Infinite simulation setting...\n";
        GridObject grid(10, 10, false);
        FileManager fileMan("test_input.txt", "output");
        SimManager sim(0);  // 0 means infinite
        
        for(int i = 0; i < 100; i++) {
            int result = sim.iterate(&grid, &fileMan, false, false);
            assert(result == 0);
        }
    }
    
    {
        std::cout << "Test 6: Combined hash and iteration limit...\n";
        GridObject grid(10, 10, false);
        FileManager fileMan("test_input.txt", "output");
        SimManager sim(10);
        
        grid.addCell(1, 1, CellType::STATIC_ALIVE);
        
        int result = sim.iterate(&grid, &fileMan, false, true);
        assert(result == 0);
        result = sim.iterate(&grid, &fileMan, false, true);
        assert(result == 2);
    }

    std::cout << "All SimManager tests passed!\n";
}

int main() {
    runTests();
    return 0;
}