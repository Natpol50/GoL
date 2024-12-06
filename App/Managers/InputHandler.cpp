#include "InputHandler.hpp"


void InputHandler::handleMouseClick(const sf::Event& event, GridObject* grid, PatternManager& patterns) {
    if (event.mouseButton.button == sf::Mouse::Left) {
        isMouseDown = (event.type == sf::Event::MouseButtonPressed);
        if (isMouseDown) {
            sf::Vector2i gridPos = manager->windowToGrid(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
            grid->addCell(gridPos.x, gridPos.y, CellType::ALIVE);
        }
    } else if (event.mouseButton.button == sf::Mouse::Right) {
        isRightMouseDown = (event.type == sf::Event::MouseButtonPressed);
        if (isRightMouseDown && patterns.getSelectedIndex() >= 0) {
            sf::Vector2i gridPos = manager->windowToGrid(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
            patterns.placePattern(grid, gridPos.x, gridPos.y);
        }
    }
}

void InputHandler::handleMouseMove(const sf::Event& event, GridObject* grid, PatternManager& patterns) {
    sf::Vector2i currentPos(event.mouseMove.x, event.mouseMove.y);
    sf::Vector2i gridPos = manager->windowToGrid(currentPos);
    
    if (isMouseDown) {
        grid->addCell(gridPos.x, gridPos.y, CellType::ALIVE);
    } else if (isRightMouseDown && patterns.getSelectedIndex() >= 0) {
        patterns.placePattern(grid, gridPos.x, gridPos.y);
    }
    
    lastMousePos = currentPos;
}

void InputHandler::processEvents(sf::Event& event, GridObject* grid, bool& isPaused, float& simulationSpeed) {
    if (event.type == sf::Event::Closed)
        manager->getWindow().close();
    else if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased)
        handleMouseClick(event, grid, *patternManager);
    else if (event.type == sf::Event::MouseMoved)
        handleMouseMove(event, grid, *patternManager);
    else if (event.type == sf::Event::KeyPressed)
        handleKeyPress(event);
}
void InputHandler::handleKeyPress(const sf::Event& event) {
    switch (event.key.code) {
        case sf::Keyboard::Space:
            isPaused = !isPaused;
            break;
            
        case sf::Keyboard::Right:
            if (isPaused) {
                needUpdate = true;
            }
            break;
            
        case sf::Keyboard::Up:
            simulationSpeed = std::min(simulationSpeed * 1.5f, 10.0f);
            break;
            
        case sf::Keyboard::Down:
            simulationSpeed = std::max(simulationSpeed * 0.75f, 0.5f);
            break;
            
        default:
            break;
    }
}