#ifndef GAMEOFLIFEGUI_HPP
#define GAMEOFLIFEGUI_HPP

#include "Managers/SFMLManager.hpp"
#include "Managers/InputHandler.hpp"
#include "Managers/SimManager.hpp"

class GameOfLifeGUI {
private:
    GridObject* grid;
    SimManager* simManager;
    FileManager* fileManager;
    PatternManager* patternManager;
    SFMLManager* sfmlManager;
    InputHandler* inputHandler;
    
    bool isPaused;
    float simulationSpeed;
    sf::Clock clock;

public:
    GameOfLifeGUI(const std::string& inputPath, const std::string& outputDir);
    ~GameOfLifeGUI();
    void run();
    void initialize(const std::string& inputPath, const std::string& outputDir);
};

#endif // GAMEOFLIFEGUI_HPP