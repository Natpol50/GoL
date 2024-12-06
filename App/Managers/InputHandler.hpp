#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <SFML/Graphics.hpp>
#include "SFMLManager.hpp"
#include "GridObject.hpp"
#include "PatternManager.hpp"

class InputHandler {
private:
    SFMLManager* manager;
    PatternManager* patternManager;
    bool isMouseDown;
    bool isRightMouseDown;
    sf::Vector2i lastMousePos;
    bool& isPaused;
    float& simulationSpeed;
    bool needUpdate;

public:
    InputHandler(SFMLManager* manager, PatternManager* patterns, bool& paused, float& speed)
        : manager(manager)
        , patternManager(patterns)
        , isMouseDown(false)
        , isRightMouseDown(false)
        , isPaused(paused)
        , simulationSpeed(speed)
        , needUpdate(false) {}

    void handleMouseClick(const sf::Event& event, GridObject* grid, PatternManager& patterns);
    void handleKeyPress(const sf::Event& event);
    void handleMouseMove(const sf::Event& event, GridObject* grid, PatternManager& patterns);
    void processEvents(sf::Event& event, GridObject* grid, bool& isPaused, float& simulationSpeed);
    bool getNeedUpdate() const { return needUpdate; }
    void clearNeedUpdate() { needUpdate = false; }
};

#endif // INPUTHANDLER_HPP