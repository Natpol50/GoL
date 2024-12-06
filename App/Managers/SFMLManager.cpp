#include "SFMLManager.hpp"

SFMLManager::SFMLManager() : window(sf::VideoMode(1200, 800), "Game of Life"), cellSize(20.f), isPanelVisible(true) {
    window.setFramerateLimit(60);
    
    if (!font.loadFromFile("arial.ttf")) {
        // Handle font loading error
    }
    
    setupViews();
    
    // Setup UI elements
    statsPanel.setSize(sf::Vector2f(200, 150));
    statsPanel.setPosition(window.getSize().x - 210, window.getSize().y - 160);
    statsPanel.setFillColor(sf::Color(50, 50, 50, 200));
    
    controlPanel.setSize(sf::Vector2f(200, 300));
    controlPanel.setPosition(window.getSize().x - 210, 10);
    controlPanel.setFillColor(sf::Color(50, 50, 50, 200));
    
    // Setup text elements
    iterationText.setFont(font);
    cellCountText.setFont(font);
    iterationText.setCharacterSize(14);
    cellCountText.setCharacterSize(14);
}

void SFMLManager::setupViews() {
    gridView = window.getDefaultView();
    uiView = window.getDefaultView();
}

void SFMLManager::updateCellShapes(const GridObject* grid) {
    cellShapes.clear();
    
    for (const auto& [pos, cell] : grid->cellmap) {
        sf::RectangleShape shape(sf::Vector2f(cellSize - 1, cellSize - 1));
        shape.setPosition(pos.first * cellSize, pos.second * cellSize);
        
        switch(cell->getDisplay()) {
            case CellType::ALIVE:
                shape.setFillColor(sf::Color::White);
                break;
            case CellType::STATIC_DEAD:
                shape.setFillColor(sf::Color::Red);
                break;
            case CellType::STATIC_ALIVE:
                shape.setFillColor(sf::Color::Green);
                break;
        }
        
        cellShapes.push_back(shape);
    }
}

void SFMLManager::updateUI(const GridObject* grid, int iteration) {
    iterationText.setString("Iteration: " + std::to_string(iteration));
    iterationText.setPosition(window.getSize().x - 200, window.getSize().y - 150);
    
    cellCountText.setString("Cells: " + std::to_string(grid->cellmap.size()));
    cellCountText.setPosition(window.getSize().x - 200, window.getSize().y - 130);
}

void SFMLManager::render(const GridObject* grid, int iteration) {
    window.clear(sf::Color(20, 20, 20));
    
    // Draw grid
    window.setView(gridView);
    updateCellShapes(grid);
    for (const auto& shape : cellShapes) {
        window.draw(shape);
    }
    
    // Draw UI
    window.setView(uiView);
    if (isPanelVisible) {
        window.draw(statsPanel);
        window.draw(controlPanel);
        updateUI(grid, iteration);
        window.draw(iterationText);
        window.draw(cellCountText);
    }
    
    window.display();
}

sf::Vector2i SFMLManager::windowToGrid(sf::Vector2i windowPos) {
    sf::Vector2f worldPos = window.mapPixelToCoords(windowPos, gridView);
    return sf::Vector2i(worldPos.x / cellSize, worldPos.y / cellSize);
}

sf::RenderWindow& SFMLManager::getWindow() {
    return window;
}