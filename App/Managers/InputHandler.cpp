#include "InputHandler.hpp"

void InputHandler::handleMouseClick(const sf::Event& event, GridObject* grid, PatternManager& patterns) {
    sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);

    if (event.mouseButton.button == sf::Mouse::Left) {
        // Vérifier le bouton save d'abord
        if (event.type == sf::Event::MouseButtonPressed && manager->checkSaveButtonClick(mousePos)) {
            // Logique de sauvegarde
            auto now = std::time(nullptr);
            auto tm = *std::localtime(&now);
            std::ostringstream filename;
            filename << "save_" << std::put_time(&tm, "%Y%m%d_%H%M%S");
            
            if (fileManager->SaveState(grid, filename.str())) {
                std::cout << "State saved to: " << filename.str() << std::endl;
            } else {
                std::cerr << "Failed to save state!" << std::endl;
            }
            return;
        }

        // Gestion des clics sur la grille
        if (event.type == sf::Event::MouseButtonPressed) {
            isMouseDown = true;
            sf::Vector2i gridPos = manager->windowToGrid(mousePos);
            grid->addCell(gridPos.x, gridPos.y, CellType::ALIVE);
            lastGridPos = gridPos;
            hasLastGridPos = true;
        }
        else if (event.type == sf::Event::MouseButtonReleased) {
            isMouseDown = false;
            hasLastGridPos = false;
        }
    } 
    else if (event.mouseButton.button == sf::Mouse::Right) {
        isRightMouseDown = (event.type == sf::Event::MouseButtonPressed);
        if (isRightMouseDown && patterns.getSelectedIndex() >= 0) {
            sf::Vector2i gridPos = manager->windowToGrid(mousePos);
            patterns.placePattern(grid, gridPos.x, gridPos.y);
        }
    }
}

void InputHandler::handleMouseMove(const sf::Event& event, GridObject* grid, PatternManager& patterns) {
    sf::Vector2i currentPos(event.mouseMove.x, event.mouseMove.y);
    manager->updateSaveButtonHover(currentPos);

    sf::Vector2i gridPos = manager->windowToGrid(currentPos);
    
    if (isMouseDown) {
        if (!hasLastGridPos || gridPos != lastGridPos) {
            grid->addCell(gridPos.x, gridPos.y, CellType::ALIVE);
            lastGridPos = gridPos;
            hasLastGridPos = true;
        }
    } 
    else if (isRightMouseDown && patterns.getSelectedIndex() >= 0) {
        patterns.placePattern(grid, gridPos.x, gridPos.y);
    }
    
    lastMousePos = currentPos;
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
            simulationSpeed = std::min(simulationSpeed * 1.5f, 1000.0f);
            break;
        case sf::Keyboard::Down:
            simulationSpeed = std::max(simulationSpeed * 0.75f, 0.25f);
            break;
        default:
            break;
    }
}

void InputHandler::processEvents(sf::Event& event, GridObject* grid) {
    if (event.type == sf::Event::Closed)
        manager->getWindow().close();
    else if (event.type == sf::Event::MouseButtonPressed || 
             event.type == sf::Event::MouseButtonReleased)
        handleMouseClick(event, grid, *patternManager);
    else if (event.type == sf::Event::MouseMoved)
        handleMouseMove(event, grid, *patternManager);
    else if (event.type == sf::Event::KeyPressed)
        handleKeyPress(event);
}