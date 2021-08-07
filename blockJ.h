#ifndef _BLOCK_J_H
#define _BLOCK_J_H
#include "block.h"

using namespace std;

class Cell;

class BlockJ : public Block {
public:
    BlockJ(Cell *component, vector<vector<int>> coord, int curLevel, vector<vector<int>> rotation, int stage);
};

#endif //BIQUAD_BLOCKJ_H
