#include <iostream>
#include <fstream>
#include "Managers/FileManager.hpp"

void createTestFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        throw std::runtime_error("Could not create test file");
    }
    file << "10 8 1\n"
         << "0 0 0 0 0 0 0 0\n"
         << "0 0 1 1 1 0 0 0\n"
         << "0 0 0 0 0 0 0 0\n"
         << "0 0 2 0 0 0 0 0\n"
         << "0 0 0 0 3 0 0 0\n"
         << "0 0 0 0 0 0 0 0\n"
         << "0 0 0 0 0 0 0 0\n"
         << "0 0 0 0 0 0 0 0\n";
}

void printTestResult(const std::string& testName, bool success) {
    std::cout << (success ? "[✓] " : "[✗] ") << testName << std::endl;
}

void testLoadInitialState() {
    std::cout << "\nTesting LoadInitialState..." << std::endl;

    createTestFile("test_input.txt");
    FileManager manager("test_input.txt", "output");
    
    try {
        GridObject grid = manager.LoadInitialState();
        
        grid.print();
        
        const Cell* cell;
        cell = grid.getCellAt(2, 1);
        printTestResult("Glider cell exists", cell && cell->getDisplay() == CellType::ALIVE);
        
        cell = grid.getCellAt(2, 3);
        printTestResult("Static dead cell exists", cell && cell->getDisplay() == CellType::STATIC_DEAD);
        
        cell = grid.getCellAt(4, 4);
        printTestResult("Static alive cell exists", cell && cell->getDisplay() == CellType::STATIC_ALIVE);
        
        std::cout << "\nInitial grid state:" << std::endl;
        grid.print();
        
    } catch (const std::exception& e) {
        std::cout << "Error during load: " << e.what() << std::endl;
    }
}

void testSaveState() {
    std::cout << "\nTesting SaveState..." << std::endl;

    FileManager manager("test_input.txt", "output");
    
    try {
        GridObject grid = manager.LoadInitialState();
        bool saveSuccess = manager.SaveState(&grid, "test_state");
        printTestResult("Save operation", saveSuccess);
        
    } catch (const std::exception& e) {
        std::cout << "Error during save/reload: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "Starting FileManager Tests\n==========================" << std::endl;
    
    testLoadInitialState();
    testSaveState();
    
    std::cout << "\n==========================\nTests Complete" << std::endl;
    return 0;
}