#include <iostream>
#include <unistd.h>
#include <string>
#include <fstream>
#include <iomanip>

#include "GameOfLifeCLI.hpp"
#include "GameOfLifeGUI.hpp"

#define date "06/12/2024"
#define version "0.5.1"
bool mode;

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
    string outputPath = "output";
    int maxIterations = 0;
    bool verboseMode = false;

    while ((opt = getopt(argc, argv, "p:vo:i:hgc")) != -1)
    {
        switch (opt)
        {
        case 'p':
            inputPath = optarg;
            break;

        case 'v':
            verboseMode = true;
            cout << "\033[1;32m" << std::left
                 << "┌────────────────────────────────────┐\n"
                 << "│        Adaptive Horizon            │\n"
                 << "├────────────────────────────────────┤\n"
                 << "│ Creators: " << std::setw(20) << "POLETTE Nathan" << "     │\n"
                 << "│           " << std::setw(20) << "LEMARINEL Océane" << "      │\n"
                 << "│                                    │\n"
                 << "│ Last Update: " << std::setw(15) << date << "       │\n"
                 << "│ Version:     " << std::setw(15) << version << "       │\n"
                 << "└────────────────────────────────────┘\033[0m\n";
            exit(0);
            break;

        case 'o':
            outputPath = optarg;
            break;

        case 'i':
            maxIterations = std::stoi(optarg);
            break;

        case 'h':
            cout << "\n\nAdaptive Horizon \n"
                 << "\n"
                 << "\n"
                 << "-help -h     Displays help information\n\n"
                 << "-v           Displays game version and extra info about it\n\n"
                 << "-p path      Gives input file path for execution [mandatory]\n\n"
                 << "-o name      Gives folder name for iteration outputs\n\n"
                 << "-i number    Gives max iteration amount\n\n"
                 << "-g           Launches the GUI version of the game\n\n"
                 << "-c           Launches the CLI version of the game (default)\n\n";
            exit(0);
            return 0;
        case 'g':
            mode = true;
            break;
        case 'c':
            mode = false;
            break;
        default:
            cerr << "Invalid option. Use -h for help." << endl;
            mode = false;
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

    if (mode == false)
    {
        GameOfLifeCLI game(inputPath, outputPath, maxIterations);
        game.run();
        return 0;
    }
    else if (mode == true){
        GameOfLifeGUI game(inputPath, outputPath);
        game.run();
        return 0;
    }
}