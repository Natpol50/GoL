#include "FileManager.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

#ifdef _WIN32
    #include <direct.h>
    #define CREATE_DIR(dir) _mkdir(dir)
#else
    #include <sys/stat.h>
    #define CREATE_DIR(dir) mkdir(dir, 0777)
#endif

FileManager::FileManager(const std::string& input, const std::string& output)
    : inputFile(input), outputDir(output) {}

bool FileManager::createOutputDir() const {
    if (outputDir.empty()) return true;
    return CREATE_DIR(outputDir.c_str()) == 0 || errno == EEXIST;
}

std::string FileManager::buildPath(const std::string& filename) const {
    #ifdef _WIN32
        const char separator = '\\';
    #else
        const char separator = '/';
    #endif

    std::string path = outputDir;
    if (!path.empty() && path.back() != separator) {
        path += separator;
    }
    return path + filename + ".txt";
}

GridObject FileManager::LoadInitialState() const {
    std::ifstream file(inputFile);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open input file: " + inputFile);
    }

    int width, height;
    bool isToroidal;
    file >> width >> height >> isToroidal;
    
    GridObject grid(width, height);
    grid.isToroidal = isToroidal;

    std::string line;
    std::getline(file, line);  // Consume newline

    for (int y = 0; y < height; y++) {
        std::getline(file, line);
        std::istringstream iss(line);
        for (int x = 0; x < width; x++) {
            char cell;
            iss >> cell;
            
            switch (cell) {
                case '1':
                    grid.addCell(x, y, CellType::ALIVE);
                    break;
                case '2':
                    grid.addCell(x, y, CellType::STATIC_DEAD);
                    break;
                case '3':
                    grid.addCell(x, y, CellType::STATIC_ALIVE);
                    break;
                default:
                    break;  // Empty cell
            }
        }
    }

    return grid;
}

bool FileManager::SaveState(const GridObject* grid, const std::string& fileName) const {
    if (!grid) return false;

    if (!createOutputDir()) {
        return false;
    }

    std::string fullPath = buildPath(fileName);
    std::ofstream file(fullPath);
    if (!file.is_open()) {
        return false;
    }

    for (int y = 0; y < grid->height; y++) {
        for (int x = 0; x < grid->width; x++) {
            auto it = grid->cellmap.find({x, y});
            if (it == grid->cellmap.end()) {
                file << "0 ";
            } else {
                switch(it->second->getDisplay()) {
                    case CellType::ALIVE:
                        file << "1 ";
                        break;
                    case CellType::STATIC_DEAD:
                        file << "2 ";
                        break;
                    case CellType::STATIC_ALIVE:
                        file << "3 ";
                        break;
                    default:
                        file << "0 ";
                }
            }
        }
        file << "\n";
    }

    return true;
}
