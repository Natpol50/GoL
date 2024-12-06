#include <cassert>
#include "GameOfLifeCLI.hpp"

using namespace std;

int main(string inputPath = "nuh uh", string outputPath = "output", int maxIterations = 0){
    GameOfLifeCLI game;
    game.initialize();
    int status = game.run();
    assert(status == 1);
    return 0;
}
