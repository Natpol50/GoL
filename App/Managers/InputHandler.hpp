#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <SFML/Graphics.hpp>
#include "SFMLManager.hpp"
#include "GridObject.hpp"
#include "PatternManager.hpp"
#include "FileManager.hpp"
#include <ctime>
#include <iomanip>
#include <sstream>

class InputHandler {
private:
    SFMLManager* manager;
    PatternManager* patternManager;
    FileManager* fileManager;
    bool isMouseDown;
    bool isRightMouseDown;
    sf::Vector2i lastMousePos;
    sf::Vector2i lastGridPos;
    bool hasLastGridPos;
    bool& isPaused;
    float& simulationSpeed;
    bool needUpdate;

    void handleKeyPress(const sf::Event& event);

public:
    InputHandler(SFMLManager* manager, PatternManager* patterns, FileManager* fm,
                bool& paused, float& speed)
        : manager(manager)
        , patternManager(patterns)
        , fileManager(fm)
        , isMouseDown(false)
        , isRightMouseDown(false)
        , isPaused(paused)
        , simulationSpeed(speed)
        , needUpdate(false) {}

    void handleMouseClick(const sf::Event& event, GridObject* grid, PatternManager& patterns);
    void handleMouseMove(const sf::Event& event, GridObject* grid, PatternManager& patterns);
    void processEvents(sf::Event& event, GridObject* grid);
    bool getNeedUpdate() const { return needUpdate; }
    void clearNeedUpdate() { needUpdate = false; }
};

#endif // INPUTHANDLER_HPP