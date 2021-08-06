//
// Created by allen on 8/5/2021.
//

#ifndef BIQUAD_BLOCKZ_H
#define BIQUAD_BLOCKZ_H
#include "block.h"

using namespace std;

class Cell;

class BlockZ : public Block {
public:
    BlockZ(Cell *component, vector<vector<int>> coord);
};

#endif //BIQUAD_BLOCKZ_H
