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
    // Prefab selector
    sf::RectangleShape prefabButton;
    sf::Text prefabLabel;
    sf::RectangleShape prefabListPanel;
    std::vector<sf::Text> prefabItems;
    bool isPrefabOpen;

    // Help panel
    sf::RectangleShape helpButton;
    sf::Text helpLabel;
    sf::RectangleShape helpPanel;
    sf::Text helpContent;
    bool isHelpOpen;
    
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
    void setupPrefabUI();
    void setupHelpUI();
    void adjustGridView();

    void drawPrefabUI(const PatternManager& patterns);
    void drawHelpUI();
    int checkPrefabItemClick(const sf::Vector2i& mousePos) const; // returns index or -1

public:
    SFMLManager(const GridObject* grid);
    void handleResize(unsigned int width, unsigned int height);
    void render(const GridObject* grid, int iteration, const PatternManager* patterns);
    sf::Vector2i windowToGrid(sf::Vector2i windowPos);
    sf::RenderWindow& getWindow();
    float getCellSize() const { return cellSize; }
    bool checkSaveButtonClick(const sf::Vector2i& mousePos);
    void updateSaveButtonHover(const sf::Vector2i& mousePos);
    // New GUI helpers
    void handleGUIClick(const sf::Vector2i& mousePos, PatternManager* patterns, FileManager* fileManager);
    void updateGUIHover(const sf::Vector2i& mousePos, PatternManager* patterns);
};

#endif // SFMLMANAGER_HPP