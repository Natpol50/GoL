//
// Created by oceane on 12/4/24.
//

#include "FileManager.hpp"
using namespace std;

FileManager::FileManager(std::string outputDir, std::string inputFile) : outputDir(outputDir), inputFile(inputFile) {}

GridObject FileManager::loadInitialState() {
    string height;
    string width;
    string toroidal;
    ifstream input(inputFile);
    getline(input, height);
    getline(input, width);
    getline(input, toroidal);
    GridObject gridObject(stoi(height), stoi(width), stoi(toroidal));
    vector<tuple<int, int, CellType>> cells;
    while (getline(input,line)){
        //getting all alive cells (and special ones)
        cells.push_back(make_tuple(
            stoi(line.substr(0, line.find(',')), // pos x
            stoi(line.substr(line.find(',')+1, line.find(',')), //pos y
            static_cast<CellType>(stoi(line.substr(line.find(',')+1))))))); //cell type
    }
    input.close();
    gridObject.initialize(cells);
    return gridObject;
}

int FileManager::saveState(GridObject toSave) {
    ofstream output(outputDir);
    output << toSave.height() << endl;
    output << toSave.width() << endl;

    for (Cell cell : toSave.cellmap){
        output << cell.getPosX() << "," << cell.getPosY() << "," << cell.getDisplay() << endl;
    }

    output.close();
    return 0;
}