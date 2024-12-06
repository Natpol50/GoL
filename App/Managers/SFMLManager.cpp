#include "SFMLManager.hpp"
#include <iostream>

SFMLManager::SFMLManager()
    : window(sf::VideoMode(1200, 800), "Game of Life")
    , cellSize(20.f)
    , isPanelVisible(true)
    , isSaveButtonHovered(false)
    , lastFPSTime(0.f)
    , frameCount(0)
    , fps(0.f)
    , lastIterationCount(0)
    , currentIterationCount(0)
    , ips(0.f)
{
    window.setFramerateLimit(60);

    // Try loading fonts
    try {
        if (!font.loadFromFile("arial.ttf") &&
            !font.loadFromFile("verdana.ttf") &&
            !font.loadFromFile("sansation.ttf") &&
            !font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf") &&
            !font.loadFromFile("/Library/Fonts/Arial.ttf")) {
            isPanelVisible = false;
            std::cerr << "Warning: No fonts could be loaded\n";
        }
    } catch (const std::exception& e) {
        isPanelVisible = false;
        std::cerr << "Font loading error: " << e.what() << std::endl;
    }

    setupViews();
    setupSaveButton();

    if (isPanelVisible) {
        // Setup stats panel
        statsPanel.setFillColor(sf::Color(50, 50, 50, 200));
        
        // Configure all text elements
        const std::vector<sf::Text*> texts = {
            &iterationText, &cellCountText, &fpsText, &ipsText, &saveText
        };
        
        for (auto* text : texts) {
            text->setFont(font);
            text->setCharacterSize(14);
            text->setFillColor(sf::Color::White);
        }
        
        saveText.setString("SAVE");
    }

    handleResize(window.getSize().x, window.getSize().y);
}

void SFMLManager::setupViews() {
    gridView = window.getDefaultView();
    uiView = window.getDefaultView();
    adjustGridView();
}

void SFMLManager::setupSaveButton() {
    saveButton.setSize(sf::Vector2f(SAVE_BUTTON_WIDTH, SAVE_BUTTON_HEIGHT));
    saveButton.setFillColor(sf::Color(70, 70, 70));
    saveButton.setOutlineColor(sf::Color::White);
    saveButton.setOutlineThickness(1);
}

void SFMLManager::handleResize(unsigned int width, unsigned int height) {
    // Mettre à jour la vue UI
    uiView.setSize(width, height);
    uiView.setCenter(width/2, height/2);
    
    // Calculer la hauteur disponible pour la grille
    float gridHeight = height - STATS_HEIGHT;
    
    // Mettre à jour la vue grille
    gridView.setSize(width, gridHeight);
    gridView.setCenter(width/2, gridHeight/2);
    
    // Update stats panel
    statsPanel.setSize(sf::Vector2f(width, STATS_HEIGHT));
    statsPanel.setPosition(0, height - STATS_HEIGHT);
    
    if (isPanelVisible) {
        float textY = height - STATS_HEIGHT + 15;
        
        // Position texts evenly
        iterationText.setPosition(PADDING, textY);
        cellCountText.setPosition(width/5 + PADDING, textY);
        fpsText.setPosition(2*width/5 + PADDING, textY);
        ipsText.setPosition(3*width/5 + PADDING, textY);
        
        // Position save button
        saveButton.setPosition(
            width - SAVE_BUTTON_WIDTH - PADDING,
            height - STATS_HEIGHT + (STATS_HEIGHT - SAVE_BUTTON_HEIGHT) / 2
        );
        
        // Center save text in button
        sf::FloatRect textBounds = saveText.getLocalBounds();
        saveText.setPosition(
            saveButton.getPosition().x + (SAVE_BUTTON_WIDTH - textBounds.width) / 2,
            saveButton.getPosition().y + (SAVE_BUTTON_HEIGHT - textBounds.height) / 2 - 5
        );
    }
    
    adjustGridView();
}
void SFMLManager::adjustGridView() {
    sf::Vector2f viewSize = gridView.getSize();
    float targetCellCount = 60.0f;
    cellSize = viewSize.x / targetCellCount;
    gridView.setCenter(viewSize.x / 2, (viewSize.y - STATS_HEIGHT) / 2);
}
void SFMLManager::updateFPS() {
    float currentTime = fpsClock.getElapsedTime().asSeconds();
    frameCount++;
    
    if (currentTime - lastFPSTime > 0.5f) {
        fps = frameCount / (currentTime - lastFPSTime);
        frameCount = 0;
        lastFPSTime = currentTime;
    }
}

void SFMLManager::updateIPS(int iteration) {
    float currentTime = ipsClock.getElapsedTime().asSeconds();
    currentIterationCount = iteration;
    
    if (currentTime >= 1.0f) {
        ips = (currentIterationCount - lastIterationCount) / currentTime;
        lastIterationCount = currentIterationCount;
        ipsClock.restart();
    }
}

void SFMLManager::updateCellShapes(const GridObject* grid) {
    cellShapes.clear();
    for (const auto& [pos, cell] : grid->cellmap) {
        // Créer une cellule légèrement plus petite que cellSize pour avoir une grille visible
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
    updateFPS();
    updateIPS(iteration);
    
    iterationText.setString("Iterations: " + std::to_string(iteration));
    cellCountText.setString("Living Cells: " + std::to_string(grid->cellmap.size()));
    
    std::stringstream fpsStr, ipsStr;
    fpsStr << std::fixed << std::setprecision(1) << fps << " FPS";
    ipsStr << std::fixed << std::setprecision(1) << ips << " IPS";
    fpsText.setString(fpsStr.str());
    ipsText.setString(ipsStr.str());
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
    if (isPanelVisible) {
        window.setView(uiView);
        window.draw(statsPanel);
        window.draw(saveButton);
        window.draw(saveText);
        updateUI(grid, iteration);
        window.draw(iterationText);
        window.draw(cellCountText);
        window.draw(fpsText);
        window.draw(ipsText);
    }
    
    window.display();
}

bool SFMLManager::checkSaveButtonClick(const sf::Vector2i& mousePos) {
    if (!isPanelVisible) return false;
    return saveButton.getGlobalBounds().contains(mousePos.x, mousePos.y);
}

void SFMLManager::updateSaveButtonHover(const sf::Vector2i& mousePos) {
    if (!isPanelVisible) return;
    
    bool wasHovered = isSaveButtonHovered;
    isSaveButtonHovered = saveButton.getGlobalBounds().contains(mousePos.x, mousePos.y);
    
    if (isSaveButtonHovered != wasHovered) {
        saveButton.setFillColor(isSaveButtonHovered ? 
            sf::Color(100, 100, 100) : sf::Color(70, 70, 70));
    }
}

sf::Vector2i SFMLManager::windowToGrid(sf::Vector2i windowPos) {
    sf::Vector2f worldPos = window.mapPixelToCoords(windowPos, gridView);
    return sf::Vector2i(worldPos.x / cellSize, worldPos.y / cellSize);
}

sf::RenderWindow& SFMLManager::getWindow() {
    return window;
}