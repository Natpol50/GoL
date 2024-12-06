#include "GameOfLifeGUI.hpp"

GameOfLifeGUI::GameOfLifeGUI(const std::string& inputPath, const std::string& outputDir) {
    fileManager = new FileManager(inputPath, outputDir);
    grid = new GridObject(fileManager->LoadInitialState());
    simManager = new SimManager(0);
    
    patternManager = new PatternManager();
    sfmlManager = new SFMLManager();
    inputHandler = new InputHandler(sfmlManager, patternManager, fileManager, isPaused, simulationSpeed);
    
    isPaused = true;
    simulationSpeed = 1.0f;
}

GameOfLifeGUI::~GameOfLifeGUI() {
    delete grid;
    delete simManager;
    delete fileManager;
    delete patternManager;
    delete sfmlManager;
    delete inputHandler;
}

void GameOfLifeGUI::run() {
    sf::Event event;
    float accumulator = 0.0f;
    
    while (sfmlManager->getWindow().isOpen()) {
        while (sfmlManager->getWindow().pollEvent(event)) {
            inputHandler->processEvents(event, grid);
        }
        
        if (!isPaused) {
            float dt = clock.restart().asSeconds();
            accumulator += dt;
            
            if (accumulator >= 1.0f / simulationSpeed) {
                simManager->iterate(grid, fileManager, true, true);
                accumulator = 0.0f;
            }
        }
        
        sfmlManager->render(grid, simManager->getCurrentIterationCount());
    }
}