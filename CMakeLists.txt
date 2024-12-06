cmake_minimum_required(VERSION 3.10)  # Changed to 3.10 as 3.30 doesn't exist yet
project(GoL)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML package
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/App
    ${CMAKE_SOURCE_DIR}/App/Cell
    ${CMAKE_SOURCE_DIR}/App/Grid
    ${CMAKE_SOURCE_DIR}/App/Managers
)

# Add executable with source files
add_executable(GoL
    App/Cell/AliveCell.cpp
    App/Cell/AliveCell.hpp
    App/Cell/AliveStaticC.cpp
    App/Cell/AliveStaticC.hpp
    App/Cell/Cell.cpp
    App/Cell/Cell.hpp
    App/Cell/CellFactory.cpp
    App/Cell/CellFactory.hpp
    App/Cell/CellType.hpp
    App/Cell/DeadStaticC.cpp
    App/Cell/DeadStaticC.hpp
    App/Grid/GridObject.cpp
    App/Grid/GridObject.hpp
    App/Managers/PatternLibrary.hpp
    App/Managers/PatternManager.cpp
    App/Managers/PatternManager.hpp
    App/Managers/FileManager.cpp
    App/Managers/FileManager.hpp
    App/Managers/HashHistoryManager.cpp
    App/Managers/HashHistoryManager.hpp
    App/Managers/SimManager.cpp
    App/Managers/SimManager.hpp
    App/Managers/SFMLManager.cpp
    App/Managers/SFMLManager.hpp
    App/Managers/InputHandler.cpp
    App/Managers/InputHandler.hpp
    App/GameOfLifeCLI.cpp
    App/GameOfLifeCLI.hpp
    App/GameOfLifeGUI.cpp
    App/GameOfLifeGUI.hpp  # Changed from .cpp to .hpp
    App/main.cpp
)

# Link SFML libraries
target_link_libraries(${PROJECT_NAME}
    sfml-graphics
    sfml-window
    sfml-system
)

# Optional: Add compiler flags if needed
if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()
