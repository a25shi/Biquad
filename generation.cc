#include "generation.h"
int generation::getLevel() {
    return level;
}

void generation::readFile(string inputfile = file) {
    char input;
    std::ifstream open(inputfile);
    while (open >> input) {
        blocks.emplace_back(input);
    }
}

void generation::swapRandom(bool random, std::string file) {
    this->file = file;
    if (random == true) {
        readFile(file);
    }
    isRandom = random;
    index = 0;
}