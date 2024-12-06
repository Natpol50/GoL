#include <iostream>
#include <unistd.h>
#include <string>
#include <fstream>
#include <iomanip>

#include "GameOfLifeCLI.hpp"

#define date "06/12/2024"
#define version "0.5.1"

using namespace std;

bool validateFile(const std::string &filename)
{
    std::ifstream file(filename);
    return file.good();
}

int main(int argc, char *argv[])
{
    int opt;
    string inputPath;
    string outputPath;
    int maxIterations = 0; // Initialize to 0
    bool verboseMode = false;

    while ((opt = getopt(argc, argv, "p:vo:i:h")) != -1)
    {
        switch (opt)
        {
        case 'p':
            inputPath = optarg;
            break;

        case 'v':
            verboseMode = true;
            cout << std::left
                 << "┌────────────────────────────────────┐\n"
                 << "│        Adaptive Horizon           │\n"
                 << "├────────────────────────────────────┤\n"
                 << "│ Creators: " << std::setw(20) << "POLETTE Nathan" << " │\n"
                 << "│           " << std::setw(20) << "LEMARINEL Océane" << " │\n"
                 << "│                                    │\n"
                 << "│ Last Update: " << std::setw(15) << date << "   │\n"
                 << "│ Version:     " << std::setw(15) << version << "   │\n"
                 << "└────────────────────────────────────┘\n";
            break;

        case 'o':
            outputPath = optarg;
            break;

        case 'i':
            maxIterations = std::stoi(optarg);
            break;

        case 'h':
            cout << "Adaptive Horizon \n"
                 << "\n"
                 << "\n"
                 << "-help -h     Displays help information\n\n"
                 << "-v           Displays game version and extra info about it\n\n"
                 << "-p path      Gives input file path for execution [mandatory]\n\n"
                 << "-o name      Gives folder name for iteration outputs\n\n"
                 << "-i number    Gives max iteration amount\n\n";
            return 0;

        default:
            cerr << "Invalid option. Use -h for help." << endl;
            return 1;
        }
    }

    while (inputPath.empty() || !validateFile(inputPath))
    {
        cout << "Input path not provided or file not found. Please provide a valid file name/path: ";
        std::getline(cin, inputPath);
    }

    if (verboseMode)
    {
        cout << "Input Path: " << inputPath << endl;
        cout << "Output Path: " << (outputPath.empty() ? "Not specified" : outputPath) << endl;
        cout << "Max Iterations: " << (maxIterations > 0 ? std::to_string(maxIterations) : "Unlimited") << endl;
    }

    GameOfLifeCLI game(inputPath, outputPath, maxIterations);
    game.run();
    return 0;
}