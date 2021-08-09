#ifndef _BLOCK_S_H_
#define _BLOCK_S_H_
#include "block.h"

using namespace std;

class Cell;

class BlockS : public Block {
public:
    BlockS(Cell *component, vector<vector<int>> coord, int curLevel, vector<vector<int>> rotation, int stage);
};


#endif //BIQUAD_BLOCKS_H
