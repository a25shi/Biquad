#include "level0.h"

level0::level0(std::string file) : generation{0}, file{file}{
    readFile();
}

char level0::genBlock() {
    if (index >= blocks.size()) {
        index == 0;
    }
    return blocks[index++];
}

void level0::readFile() {
    char input;
    std::ifstream open(file);
    while (open >> input) {
        blocks.emplace_back(input);
    }
}