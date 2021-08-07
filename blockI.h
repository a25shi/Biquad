#ifndef _BLOCK_I_H_
#define _BLOCK_I_H_
#include "block.h"

using namespace std;

class Cell;

class BlockI : public Block {
public:
    BlockI(Cell *component, vector<vector<int>> coord, int curLevel, vector<vector<int>> rotation, int stage);
};


#endif //BIQUAD_BLOCKI_H
