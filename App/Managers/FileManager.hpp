#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include "Grid/GridObject.hpp"

class FileManager {
private:
    std::string inputFile;
    std::string outputDir;

    std::string buildPath(const std::string& filename) const;
    bool createOutputDir() const;  // Nouvelle méthode

public:
    FileManager();
    FileManager(const std::string& input, const std::string& output);
    GridObject LoadInitialState() const;
    bool SaveState(const GridObject* grid, const std::string& fileName) const;
};

#endif // FILE_MANAGER_H