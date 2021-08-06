#ifndef BIQUAD_BLOCKI_H
#define BIQUAD_BLOCKI_H
#include "block.h"

using namespace std;

class Cell;

class BlockI : public Block {
public:
    BlockI(Cell *component, vector<vector<int>> coord);
};


#endif //BIQUAD_BLOCKI_H
