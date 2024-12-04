//
// Created by oceane on 12/4/24.
//

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include "GridObject.hpp"

class FileManager {
private:
    std::string outputDir;
    std::string inputFile;
public:
    FileManager(std::string outputDir, std::string inputFile);
    GridObject loadInitialState();
    int saveState(GridObject toSave);
};



#endif //FILEMANAGER_H
