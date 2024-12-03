cmake_minimum_required(VERSION 3.30)
project(GoL)

set(CMAKE_CXX_STANDARD 14)

include_directories(App/Cell)
include_directories(App/GUI)

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
    App/Tests/CellTests.cpp
    App/main.cpp)
