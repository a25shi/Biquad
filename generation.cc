#include "generation.h"
int generation::getLevel() {
    return level;
}

void generation::readFile() {
    char input;
    std::ifstream open(file);
    while (open >> input) {
        blocks.emplace_back(input);
    }
}

void generation::swapRandom(bool random, std::string file) {
    this->file = file;
    if (random == true) {
        readFile();
    }
    isRandom = random;
    index = 0;
}