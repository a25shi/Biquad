#include "level1.h"

level1::level1() : generation{1}{}

char level1::genBlock() {
    int seed = rand() % 12 + 1;
    if (seed % 6 == 0) {
        return 'O';
    }
    else if (seed % 5 == 0) {
        return 'T';
    }
    else if (seed % 4 == 0) {
        return 'I';
    }
    else if (seed % 3 == 0) {
        return 'J';
    }
    else if (seed % 2 == 0) {
        return 'S';
    }
    else if (seed == 1) {
        return 'Z';
    }
    else if (seed % 1 == 0) {
        return 'L';
    }

    return ' ';
}