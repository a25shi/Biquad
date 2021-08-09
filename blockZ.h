#ifndef _BLOCK_Z_H
#define _BLOCK_Z_H
#include "block.h"

using namespace std;

class Cell;

class BlockZ : public Block {
public:
    BlockZ(Cell *component, vector<vector<int>> coord, int curLevel, vector<vector<int>> rotation, int stage);
};

#endif //BIQUAD_BLOCKZ_H
