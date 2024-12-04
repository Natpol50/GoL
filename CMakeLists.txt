cmake_minimum_required(VERSION 3.30)
project(GoL)

set(CMAKE_CXX_STANDARD 14)

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
    App/Grid/Grid.cpp
    App/Grid/Grid.hpp
    App/Tests/CellTests.cpp
    App/Grid/Test.cpp)
