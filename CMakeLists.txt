cmake_minimum_required(VERSION 3.10)
project(GoL)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files list
set(SOURCE_FILES
    App/Cell/AliveCell.cpp
    App/Cell/AliveStaticC.cpp
    App/Cell/Cell.cpp
    App/Cell/CellFactory.cpp
    App/Cell/DeadStaticC.cpp
    App/Grid/GridObject.cpp
    App/Managers/PatternManager.cpp
    App/Managers/FileManager.cpp
    App/Managers/HashHistoryManager.cpp
    App/Managers/SimManager.cpp
    App/Managers/SFMLManager.cpp
    App/Managers/InputHandler.cpp
    App/GameOfLifeCLI.cpp
    App/GameOfLifeGUI.cpp
    App/main.cpp
)

# Include directories
set(INCLUDE_DIRS
    ${CMAKE_SOURCE_DIR}/App
    ${CMAKE_SOURCE_DIR}/App/Cell
    ${CMAKE_SOURCE_DIR}/App/Grid
    ${CMAKE_SOURCE_DIR}/App/Managers
)

# Linux Build
if(UNIX)
    # Linux compiler flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-reorder")
    
    # Find SFML for Linux
    find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
    
    # Linux executable
    add_executable(GoL_Linux ${SOURCE_FILES})
    target_include_directories(GoL_Linux PRIVATE ${INCLUDE_DIRS})
    target_link_libraries(GoL_Linux
        sfml-graphics
        sfml-window
        sfml-system
    )
endif()