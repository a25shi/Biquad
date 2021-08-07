#ifndef _BLOCK_T_H_
#define _BLOCK_T_H_
#include "block.h"

using namespace std;

class Cell;

class BlockT : public Block {
public:
    BlockT(Cell *component, vector<vector<int>> coord, int curLevel, vector<vector<int>> rotation, int stage);
};



#endif //BIQUAD_BLOCKT_H
