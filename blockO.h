#ifndef _BLOCK_O_H_
#define _BLOCK_O_H_
#include "block.h"

using namespace std;

class Cell;

class BlockO : public Block {
public:
    BlockO(Cell *component, vector<vector<int>> coord, int curLevel);
};


#endif //BIQUAD_BLOCKO_H
