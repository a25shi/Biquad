#ifndef BIQUAD_BLOCKJ_H
#define BIQUAD_BLOCKJ_H
#include "block.h"

using namespace std;

class Cell;

class BlockJ : public Block {
public:
    BlockJ(Cell *component, vector<vector<int>> coord);
};

#endif //BIQUAD_BLOCKJ_H
