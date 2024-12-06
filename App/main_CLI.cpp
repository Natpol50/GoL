#include <iostream>
#include <unistd.h>
#include <string>
#include <fstream>
#include <cassert>

#include "GameOfLifeCLI.hpp"

using namespace std;


bool validateFile(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

int main(int argc, char *argv[])
{
    int opt;
    string inputPath;
    string outputPath;
    int maxIterations;

    while ((opt = getopt(argc, argv, "s:vf:")) != -1)
    {
        switch (opt)
        {
        case 'p':
            inputPath = optarg;                
            break;

        case 'v':
            cout << "Adaptive Horizon \n"
            << "Made by: POLETTE Nathan & LEMARINEL Océane \n"
            <<"Last update: 06/12/2024 \n"
            <<"Version 0.28 \n";
            break;

        case 'o':
            outputPath = optarg;
            break;

        case 'i':
            maxIterations = atoi(optarg);
            break;

        case 'h':
            cout << "Adaptive Horizon \n"
            <<"\n"
            <<"\n"
            <<"-help -h     Displays help information\n\n"
            <<"-v           Displays game version and extra info about it\n\n"
            <<"-p path      Gives input file path for execution [mandatory]\n\n"
            <<"-o name      Gives folder name for iteration outputs\n\n"
            <<"-i number    Gives max iteration amount\n\n";
            return 0;
        default :
            break;
        }
    }
    
    while(!validateFile(inputPath)){
        cout << "input path not provided / can't find file \n please provide file name / path";
        cin >> inputPath ;
    }

    //
    // Finally running everything according to parameters
    //

    GameOfLifeCLI game(inputPath, outputPath, maxIterations);
    int status = game.run();
    assert(status == 1 || status == 2);
    return 0;
}
