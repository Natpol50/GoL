#include "SFMLManager.hpp"
#include <iostream>
#include <algorithm>

SFMLManager::SFMLManager(const GridObject* grid)
    : window(sf::VideoMode(1200, 800), "Game of Life", sf::Style::Close | sf::Style::Titlebar)
    , cellSize(20.f)
    , isPanelVisible(true)
    , isSaveButtonHovered(false)
    , lastFPSTime(0.f)
    , frameCount(0)
    , fps(0.f)
    , lastIterationCount(0)
    , currentIterationCount(0)
    , ips(0.f)
    , currentGrid(grid)
{
    window.setFramerateLimit(10000);

    sf::Image icon;
    if (icon.loadFromFile("icons/favicon.png")) {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
    // Try loading fonts
    try {
        if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf") &&
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
    setupPrefabUI();
    setupHelpUI();

    if (isPanelVisible) {
        statsPanel.setFillColor(sf::Color(50, 50, 50, 200));
        
        const std::vector<sf::Text*> texts = {
            &iterationText, &cellCountText, &fpsText, &ipsText, &saveText, &prefabLabel, &helpLabel, &helpContent
        };

        for (auto* text : texts) {
            text->setFont(font);
            text->setCharacterSize(14);
            text->setFillColor(sf::Color::White);
        }

        // help content is slightly smaller
        helpContent.setCharacterSize(12);

        saveText.setString("SAVE");
        prefabLabel.setString("Prefab: -");
        helpLabel.setString("HELP");
    }

    handleResize(window.getSize().x, window.getSize().y);
}

void SFMLManager::setupPrefabUI() {
    isPrefabOpen = false;
    prefabButton.setSize(sf::Vector2f(150.f, SAVE_BUTTON_HEIGHT));
    prefabButton.setFillColor(sf::Color(70, 70, 70));
    prefabButton.setOutlineColor(sf::Color::White);
    prefabButton.setOutlineThickness(1);

    prefabLabel.setCharacterSize(14);
    prefabLabel.setFillColor(sf::Color::White);
    prefabListPanel.setFillColor(sf::Color(40, 40, 40, 230));
    prefabListPanel.setOutlineColor(sf::Color::White);
    prefabListPanel.setOutlineThickness(1);
}

void SFMLManager::setupHelpUI() {
    isHelpOpen = false;
    helpButton.setSize(sf::Vector2f(60.f, SAVE_BUTTON_HEIGHT));
    helpButton.setFillColor(sf::Color(70, 70, 70));
    helpButton.setOutlineColor(sf::Color::White);
    helpButton.setOutlineThickness(1);

    helpLabel.setCharacterSize(14);
    helpLabel.setFillColor(sf::Color::White);

    helpPanel.setFillColor(sf::Color(30, 30, 30, 230));
    helpPanel.setOutlineColor(sf::Color::White);
    helpPanel.setOutlineThickness(1);

    helpContent.setCharacterSize(12);
    helpContent.setFillColor(sf::Color::White);
    helpContent.setString("Left-click: draw cells\nRight-click: place selected prefab\nSpace: pause\nArrow keys: select prefab / speed");
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
    uiView.setSize(width, height);
    uiView.setCenter(width/2, height/2);
    
    gridView.setSize(width, height - STATS_HEIGHT);
    gridView.setCenter(width/2, gridView.getSize().y/2);
    

    statsPanel.setSize(sf::Vector2f(width, STATS_HEIGHT));
    statsPanel.setPosition(0, height - STATS_HEIGHT);
    
    if (isPanelVisible) {
        // Reserve space for left widgets (prefab) and right widgets (save+help)
        float textY = height - STATS_HEIGHT + 15;

        // Stats panel layout (bottom bar)
        float elementWidth = width / 5.0f;
        iterationText.setPosition(elementWidth * 0.5f - iterationText.getLocalBounds().width/2, textY);
        cellCountText.setPosition(elementWidth * 1.5f - cellCountText.getLocalBounds().width/2, textY);
        fpsText.setPosition(elementWidth * 2.5f - fpsText.getLocalBounds().width/2, textY);
        ipsText.setPosition(elementWidth * 3.5f - ipsText.getLocalBounds().width/2, textY);

        // Save button (bottom right)
        float saveX = width - SAVE_BUTTON_WIDTH - PADDING;
        saveButton.setPosition(saveX, height - STATS_HEIGHT + (STATS_HEIGHT - SAVE_BUTTON_HEIGHT) / 2);
        sf::FloatRect textBounds = saveText.getLocalBounds();
        saveText.setPosition(
            saveButton.getPosition().x + (SAVE_BUTTON_WIDTH - textBounds.width) / 2,
            saveButton.getPosition().y + (SAVE_BUTTON_HEIGHT - textBounds.height) / 2 - 5
        );

        // Prefab selector (Top Right overlay)
        float prefabX = width - prefabButton.getSize().x - PADDING;
        float prefabY = PADDING;
        prefabButton.setPosition(prefabX, prefabY);
        prefabLabel.setPosition(prefabButton.getPosition().x + 6, prefabButton.getPosition().y + 4);

        // Prefab list panel (below prefab button)
        prefabListPanel.setPosition(prefabX, prefabY + prefabButton.getSize().y);
        prefabListPanel.setSize(sf::Vector2f(prefabButton.getSize().x, 150.f));

        // Help button (Top Left overlay)
        helpButton.setPosition(PADDING, PADDING);
        helpLabel.setPosition(helpButton.getPosition().x + 6, helpButton.getPosition().y + 4);

        // Help panel (below help button)
        helpPanel.setPosition(PADDING, PADDING + helpButton.getSize().y);
        helpPanel.setSize(sf::Vector2f(240.f, 120.f));
        helpContent.setPosition(helpPanel.getPosition().x + 8, helpPanel.getPosition().y + 8);
    }
    
    // Adjust grid view viewport to not be covered by stats panel
    float gridRatio = (float)(height - STATS_HEIGHT) / height;
    gridView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, gridRatio));
    gridView.setSize(width, height - STATS_HEIGHT);

    adjustGridView();
}


void SFMLManager::adjustGridView() {
    // Calculate cellSize to fit grid into current view size (which matches window aspect ratio)
    sf::Vector2f viewSize = gridView.getSize();
    cellSize = std::min(viewSize.x / currentGrid->width, viewSize.y / currentGrid->height);
    
    // Center view on the grid content
    float totalGridWidth = cellSize * currentGrid->width;
    float totalGridHeight = cellSize * currentGrid->height;
    gridView.setCenter(totalGridWidth / 2.f, totalGridHeight / 2.f);
    
    // Do NOT resize gridView to match grid dimensions, as that causes stretching/squishing
    // if the aspect ratio differs from the viewport.
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
        sf::RectangleShape shape(sf::Vector2f(cellSize - 1, cellSize - 1));
        shape.setPosition(pos.first * cellSize, pos.second * cellSize);
        
        switch(cell->getDisplay()) {
            case CellType::ALIVE:
                shape.setFillColor(sf::Color::White);
                break;
            case CellType::STATIC_DEAD:
                shape.setFillColor(sf::Color(128, 128, 128));
                break;
            case CellType::STATIC_ALIVE:
                shape.setFillColor(sf::Color::Green);
                break;
        }
        
        cellShapes.push_back(shape);
    }
}
void SFMLManager::drawPrefabUI(const PatternManager& patterns) {
    // draw button label
    std::string label = "Prefab: ";
    const Pattern* p = patterns.getPattern(patterns.getSelectedIndex());
    if (p) label += p->name;
    prefabLabel.setString(label);
    window.draw(prefabButton);
    window.draw(prefabLabel);

    if (isPrefabOpen) {
        // Draw list panel and items
        window.draw(prefabListPanel);
        prefabItems.clear();
        float itemHeight = 20.f;
        float startY = prefabListPanel.getPosition().y + 8;
        int idx = 0;
        for (const Pattern& pat : PATTERN_LIBRARY) {
            sf::Text item;
            item.setFont(font);
            item.setCharacterSize(14);
            item.setFillColor(idx == patterns.getSelectedIndex() ? sf::Color::Cyan : sf::Color::White);
            item.setString(pat.name);
            item.setPosition(prefabListPanel.getPosition().x + 8, startY + idx * itemHeight);
            prefabItems.push_back(item);
            window.draw(prefabItems.back());
            idx++;
            if (startY + idx * itemHeight > prefabListPanel.getPosition().y + prefabListPanel.getSize().y - 8) break;
        }
    }
}

void SFMLManager::drawHelpUI() {
    window.draw(helpButton);
    window.draw(helpLabel);
    if (isHelpOpen) {
        window.draw(helpPanel);
        window.draw(helpContent);
    }
}

int SFMLManager::checkPrefabItemClick(const sf::Vector2i& mousePos) const {
    if (!isPrefabOpen) return -1;
    if (!prefabListPanel.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y)) return -1;
    float y = mousePos.y - prefabListPanel.getPosition().y - 8;
    int index = static_cast<int>(y / 20.f);
    if (index < 0) return -1;
    if (index >= (int)PATTERN_LIBRARY.size()) return -1;
    return index;
}

void SFMLManager::handleGUIClick(const sf::Vector2i& mousePos, PatternManager* patterns, FileManager* fileManager) {
    // Save button handled elsewhere; check prefab and help
    if (prefabButton.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y)) {
        isPrefabOpen = !isPrefabOpen;
        // close help if open
        if (isPrefabOpen) isHelpOpen = false;
        return;
    }

    if (isPrefabOpen) {
        int clicked = checkPrefabItemClick(mousePos);
        if (clicked >= 0) {
            patterns->setSelectedIndex(clicked);
            isPrefabOpen = false;
            return;
        }
    }

    if (helpButton.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y)) {
        isHelpOpen = !isHelpOpen;
        if (isHelpOpen) isPrefabOpen = false;
        return;
    }
}

void SFMLManager::updateGUIHover(const sf::Vector2i& mousePos, PatternManager* patterns) {
    updateSaveButtonHover(mousePos);
    bool wasHovered = prefabButton.getFillColor() == sf::Color(100,100,100);
    bool nowHovered = prefabButton.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y);
    if (nowHovered != wasHovered) {
        prefabButton.setFillColor(nowHovered ? sf::Color(100,100,100) : sf::Color(70,70,70));
    }

    bool helpWas = helpButton.getFillColor() == sf::Color(100,100,100);
    bool helpNow = helpButton.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y);
    if (helpNow != helpWas) {
        helpButton.setFillColor(helpNow ? sf::Color(100,100,100) : sf::Color(70,70,70));
    }
}
void SFMLManager::updateUI(const GridObject* grid, int iteration) {
    updateFPS();
    updateIPS(iteration);
    
    iterationText.setString("Iterations: " + std::to_string(iteration));
    cellCountText.setString("Living Cells: " + std::to_string(grid->cellmap.size()));
    
    std::stringstream fpsStr, ipsStr;
    fpsStr << std::fixed << std::setprecision(1) << fps << " FPS";
    ipsStr << std::fixed << std::setprecision(1) << ips << " IT/S";
    fpsText.setString(fpsStr.str());
    ipsText.setString(ipsStr.str());
    
    float width = window.getSize().x;
    float elementWidth = width / 5;
    float textY = window.getSize().y - STATS_HEIGHT + 15;
    
    iterationText.setPosition(elementWidth * 0.5f - iterationText.getLocalBounds().width/2, textY);
    cellCountText.setPosition(elementWidth * 1.5f - cellCountText.getLocalBounds().width/2, textY);
    fpsText.setPosition(elementWidth * 2.5f - fpsText.getLocalBounds().width/2, textY);
    ipsText.setPosition(elementWidth * 3.5f - ipsText.getLocalBounds().width/2, textY);
}


void SFMLManager::render(const GridObject* grid, int iteration, const PatternManager* patterns) {
    window.clear(sf::Color(20, 20, 20));
    
    window.setView(gridView);
    updateCellShapes(grid);
    for (const auto& shape : cellShapes) {
        window.draw(shape);
    }
    
    if (isPanelVisible) {
        window.setView(uiView);
        window.draw(statsPanel);
        window.draw(saveButton);
        window.draw(saveText);
        // draw prefab and help UI
        drawPrefabUI(*patterns);
        drawHelpUI();
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
