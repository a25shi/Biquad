#include "level2.h"

level2::level2() : generation{2} {}

char level2::genBlock() {
    int seed = rand() % 7 + 1;
    if (seed == 7) {
        return 'I';
    }
    else if (seed == 6) {
        return 'J';
    }
    else if (seed == 5) {
        return 'L';
    }
    else if (seed == 4) {
        return 'O';
    }
    else if (seed == 3) {
        return 'S';
    }
    else if (seed == 2) {
        return 'Z';
    }
    else if (seed == 1) {
        return 'T';
    }
}