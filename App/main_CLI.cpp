#include <iostream>
#include <unistd.h>
#include <string>
#include <fstream>
#include <cassert>
#include <filesystem>
#include "GameOfLifeCLI.hpp"

class CLIParser {
private:
    struct Parameters {
        std::string inputPath;
        std::string outputPath;
        int maxIterations;
        bool verboseMode;
        bool helpRequested;
    };

    static void displayVersion() {
        std::cout << "Adaptive Horizon - Game of Life\n"
                  << "Version: 0.4.7\n"
                  << "Authors: POLETTE Nathan & LEMARINEL Océane\n"
                  << "Last update: " << __DATE__ << "\n";
    }

<<<<<<< Updated upstream
    static void displayHelp() {
        std::cout << "Adaptive Horizon - Game of Life\n"
                  << "Usage: program [options]\n\n"
                  << "Options:\n"
                  << "  -h         Display this help message\n"
                  << "  -v         Display version information\n"
                  << "  -p <path>  Input file path [mandatory]\n"
                  << "  -o <path>  Output folder path for iterations\n"
                  << "  -i <num>   Maximum number of iterations (0 for unlimited)\n\n"
                  << "Example:\n"
                  << "  ./program -p input.txt -o output_folder -i 100\n";
    }
=======
int main(int argc, char *argv[])
{
    int opt;
    string inputPath;
    string outputPath = "output";
    int maxIterations = 0;
    bool verboseMode = false;
>>>>>>> Stashed changes

    static bool validateInputFile(const std::string& path) {
        if (path.empty()) {
            return false;
        }
        std::ifstream file(path);
        return file.good();
    }

<<<<<<< Updated upstream
    static bool validateOutputPath(const std::string& path) {
        if (path.empty()) {
            return true;  // Empty path is allowed
        }
        try {
            std::filesystem::create_directories(path);
            return true;
        } catch (const std::exception& e) {
            std::cerr << "Error creating output directory: " << e.what() << std::endl;
            return false;
=======
        case 'v':
            verboseMode = true;
            cout << "Adaptive Horizon \n"
                 << "Made by: POLETTE Nathan & LEMARINEL Océane \n"
                 << "Last update: 06/12/2024 \n"
                 << "Version 0.28 \n";
            break;

        case 'o':
            outputPath = optarg;
            break;

        case 'i':
            maxIterations = std::stoi(optarg);
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
            break;

        default:
            cerr << "Invalid option. Use -h for help." << endl;
            return 1;
>>>>>>> Stashed changes
        }
    }

public:
    static Parameters parseArguments(int argc, char* argv[]) {
        Parameters params = {
            .inputPath = "",
            .outputPath = "",
            .maxIterations = 0,
            .verboseMode = false,
            .helpRequested = false
        };

        int opt;
        while ((opt = getopt(argc, argv, "p:vo:i:h")) != -1) {
            switch (opt) {
                case 'p':
                    params.inputPath = optarg;
                    break;
                case 'v':
                    params.verboseMode = true;
                    displayVersion();
                    break;
                case 'o':
                    params.outputPath = optarg;
                    break;
                case 'i':
                    try {
                        params.maxIterations = std::stoi(optarg);
                        if (params.maxIterations < 0) {
                            throw std::out_of_range("Iterations must be non-negative");
                        }
                    } catch (const std::exception& e) {
                        std::cerr << "Invalid iteration count: " << e.what() << std::endl;
                        exit(1);
                    }
                    break;
                case 'h':
                    params.helpRequested = true;
                    displayHelp();
                    exit(0);
                default:
                    std::cerr << "Invalid option. Use -h for help." << std::endl;
                    exit(1);
            }
        }

        return params;
    }

    static bool validateParameters(Parameters& params) {
        bool isValid = true;

        // Validate input file
        if (!validateInputFile(params.inputPath)) {
            std::cerr << "Error: Input file not found or invalid" << std::endl;
            isValid = false;
        }

        // Validate output directory
        if (!validateOutputPath(params.outputPath)) {
            std::cerr << "Error: Cannot create or access output directory" << std::endl;
            isValid = false;
        }

        return isValid;
    }
};

int main(int argc, char* argv[]) {
    try {
        auto params = CLIParser::parseArguments(argc, argv);
        
        // If no input path provided, prompt user
        while (!CLIParser::validateParameters(params)) {
            std::cout << "Please enter input file path: ";
            std::getline(std::cin, params.inputPath);
            
            if (params.inputPath == "quit" || params.inputPath == "exit") {
                std::cout << "Program terminated by user." << std::endl;
                return 0;
            }
        }

        if (params.verboseMode) {
            std::cout << "\nConfiguration:\n"
                      << "Input Path: " << params.inputPath << "\n"
                      << "Output Path: " << (params.outputPath.empty() ? "Not specified" : params.outputPath) << "\n"
                      << "Max Iterations: " << (params.maxIterations > 0 ? std::to_string(params.maxIterations) : "Unlimited") 
                      << std::endl;
        }

        GameOfLifeCLI game(params.inputPath, params.outputPath, params.maxIterations);
        return game.run();

    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
}