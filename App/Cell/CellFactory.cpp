#include "CellFactory.hpp"

std::unique_ptr<Cell> CellFactory::createCell(int x, int y, CellType type) {
        switch (type) {
            case CellType::ALIVE:
                return std::make_unique<AliveCell>(x, y);
            case CellType::STATIC_ALIVE:
                return std::make_unique<AliveStaticC>(x, y);
            case CellType::STATIC_DEAD:
                return std::make_unique<DeadStaticC>(x, y);
            default:
                return nullptr;
        }
    }
