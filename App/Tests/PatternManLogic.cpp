#include <iostream>
#include "Managers/PatternManager.hpp"
#include "Grid/GridObject.hpp"

void printTestResult(const std::string& testName, bool success) {
    std::cout << (success ? "[✓] " : "[✗] ") << testName << std::endl;
}

void testInitialization() {
    std::cout << "\nTesting PatternManager Initialization..." << std::endl;
    
    PatternManager manager;
    bool success = (manager.getSelectedIndex() == -1);
    
    printTestResult("Initial selected index is -1", success);
}

void testIndexSelection() {
    std::cout << "\nTesting Index Selection..." << std::endl;
    
    PatternManager manager;
    bool success;
    
    success = manager.setSelectedIndex(0);
    printTestResult("Set valid index (0)", success);
    printTestResult("Get index returns 0", manager.getSelectedIndex() == 0);
    
    success = !manager.setSelectedIndex(-1);
    printTestResult("Reject negative index", success);
    
    success = !manager.setSelectedIndex(1000);
    printTestResult("Reject too large index", success);
}

void testPatternPlacement() {
    std::cout << "\nTesting Pattern Placement..." << std::endl;
    
    GridObject grid(10, 10, true);
    PatternManager manager;
    
    bool success = !manager.placePattern(&grid, 5, 5);
    printTestResult("Reject placement without selection", success);
    
    std::cout << "\nInitial empty grid:" << std::endl;
    grid.print();
    
    manager.setSelectedIndex(0);
    success = manager.placePattern(&grid, 5, 5);
    printTestResult("Place Crawler pattern", success);
    
    std::cout << "\nGrid after placing Crawler at (5,5):" << std::endl;
    grid.print();
    
    GridObject grid2(10, 10);
    manager.setSelectedIndex(1);
    success = manager.placePattern(&grid2, 4, 4);
    printTestResult("Place blinker pattern", success);
    
    std::cout << "\nGrid after placing blinker at (4,4):" << std::endl;
    grid2.print();
    
    GridObject grid3(10, 10, true);
    manager.setSelectedIndex(2);
    success = manager.placePattern(&grid3, 10, 3);
    printTestResult("Place block pattern", success);
    
    std::cout << "\nGrid after placing block at (10,3) (Toroidal + blocktest):" << std::endl;
    grid3.print();
    
    success = manager.placePattern(&grid, -1, -1);
    printTestResult("Allow placement at negative coordinates", success);
    
    std::cout << "\nGrid after attempting placement at negative coordinates:" << std::endl;
    grid.print();
}

void testGetPattern() {
    std::cout << "\nTesting Pattern Retrieval..." << std::endl;
    
    PatternManager manager;
    
    const Pattern* pattern = manager.getPattern(0);
    printTestResult("Get valid pattern", pattern != nullptr);
    if (pattern) {
        printTestResult("Pattern has correct name", pattern->name == "Crawler");
        printTestResult("Pattern has correct number of cells", pattern->cells.size() == 5);
    }
    
    pattern = manager.getPattern(-1);
    printTestResult("Return nullptr for invalid index", pattern == nullptr);
    
    pattern = manager.getPattern(1000);
    printTestResult("Return nullptr for out of bounds index", pattern == nullptr);
}

int main() {
    std::cout << "Starting PatternManager Tests\n=============================" << std::endl;
    
    testInitialization();
    testIndexSelection();
    testPatternPlacement();
    testGetPattern();
    
    std::cout << "\n=============================\nTests Complete" << std::endl;
    return 0;
}