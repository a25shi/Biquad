#include "level0.h"

level0::level0(std::string file) : generation{0,file}{
    readFile(file);
}

char level0::genBlock() {
    if (index >= blocks.size()) {
        index = 0;
    }
    return blocks[index++];
}

