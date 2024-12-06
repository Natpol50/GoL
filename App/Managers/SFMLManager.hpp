#ifndef SFMLMANAGER_HPP
#define SFMLMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "SimManager.hpp"
#include "PatternManager.hpp"

class SFMLManager {
private:
    sf::RenderWindow window;
    sf::View gridView;
    sf::View uiView;
    std::vector<sf::RectangleShape> cellShapes;
    
    sf::RectangleShape statsPanel;
    sf::RectangleShape controlPanel;
    sf::Text iterationText;
    sf::Text cellCountText;
    sf::Font font;
    
    sf::RectangleShape playButton;
    sf::RectangleShape speedSlider;
    sf::RectangleShape nextButton;
    sf::RectangleShape patternSelector;
    sf::RectangleShape saveButton;
    
    float cellSize;
    bool isPanelVisible;
    
    void updateCellShapes(const GridObject* grid);
    void updateUI(const GridObject* grid, int iteration);
    void setupViews();

public:
    SFMLManager();
    void render(const GridObject* grid, int iteration);
    sf::RenderWindow& getWindow();
    void handleResize(unsigned int width, unsigned int height);
    float getCellSize() const { return cellSize; }
    sf::Vector2i windowToGrid(sf::Vector2i windowPos);
};

#endif //SFMLMANAGER_HPP