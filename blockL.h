#ifndef _BLOCK_L_H_
#define _BLOCK_L_H_
#include "block.h"

using namespace std;

class Cell;

class BlockL : public Block {
public:
    BlockL(Cell *component, vector<vector<int>> coord, int curLevel, vector<vector<int>> rotation, int stage);
};

#endif
