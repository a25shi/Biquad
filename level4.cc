#include "level4.h"
level4::level4() : generation{4} {}

char level4::genBlock() {
    int seed = rand() % 9 + 1;
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
    else if (seed == 3 || seed == 9) {
        return 'S';
    }
    else if (seed == 2 || seed == 8) {
        return 'Z';
    }
    else if (seed == 1) {
        return 'T';
    }
}