#ifndef SFMLMANAGER_HPP
#define SFMLMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iomanip>
#include <sstream>
#include "SimManager.hpp"
#include "PatternManager.hpp"

class SFMLManager {
private:
    const GridObject* currentGrid;
    sf::RenderWindow window;
    sf::View gridView;
    sf::View uiView;
    std::vector<sf::RectangleShape> cellShapes;
    
    // UI Elements
    sf::RectangleShape statsPanel;
    sf::RectangleShape saveButton;
    sf::Text iterationText;
    sf::Text cellCountText;
    sf::Text fpsText;
    sf::Text ipsText;
    sf::Text saveText;
    sf::Font font;
    
    // Performance tracking
    sf::Clock fpsClock;
    sf::Clock ipsClock;
    float lastFPSTime;
    int frameCount;
    float fps;
    float lastIterationCount;
    float currentIterationCount;
    float ips;
    
    // State variables
    float cellSize;
    bool isPanelVisible;
    bool isSaveButtonHovered;
    
    // Constants
    static constexpr float STATS_HEIGHT = 50.f;
    static constexpr float SAVE_BUTTON_WIDTH = 80.f;
    static constexpr float SAVE_BUTTON_HEIGHT = 30.f;
    static constexpr float PADDING = 10.f;
    
    void updateCellShapes(const GridObject* grid);
    void updateUI(const GridObject* grid, int iteration);
    void updateFPS();
    void updateIPS(int iteration);
    void setupViews();
    void setupSaveButton();
    void adjustGridView();

public:
    SFMLManager(const GridObject* grid);
    void handleResize(unsigned int width, unsigned int height);
    void render(const GridObject* grid, int iteration);
    sf::Vector2i windowToGrid(sf::Vector2i windowPos);
    sf::RenderWindow& getWindow();
    float getCellSize() const { return cellSize; }
    bool checkSaveButtonClick(const sf::Vector2i& mousePos);
    void updateSaveButtonHover(const sf::Vector2i& mousePos);
};

#endif // SFMLMANAGER_HPP