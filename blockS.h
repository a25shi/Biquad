#ifndef BIQUAD_BLOCKS_H
#define BIQUAD_BLOCKS_H
#include "block.h"

using namespace std;

class Cell;

class BlockS : public Block {
public:
    BlockS(Cell *component, vector<vector<int>> coord);
};


#endif //BIQUAD_BLOCKS_H
