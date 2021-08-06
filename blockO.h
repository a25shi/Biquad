#ifndef BIQUAD_BLOCKO_H
#define BIQUAD_BLOCKO_H
#include "block.h"

using namespace std;

class Cell;

class BlockO : public Block {
public:
    BlockO(Cell *component, vector<vector<int>> coord);
};


#endif //BIQUAD_BLOCKO_H
