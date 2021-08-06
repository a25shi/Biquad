#ifndef BIQUAD_BLOCKT_H
#define BIQUAD_BLOCKT_H
#include "block.h"

using namespace std;

class Cell;

class BlockT : public Block {
public:
    BlockT(Cell *component, vector<vector<int>> coord);
};



#endif //BIQUAD_BLOCKT_H
