cmake_minimum_required(VERSION 3.30)
project(GoL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(App)

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
    App/Tests/SimManagerLogic.cpp) # This one should be the real executable, RN is it the GridObjectLogic test
