#ifndef BIQUAD_BLOCKS_H
#define BIQUAD_BLOCKS_H
#include "block.h"

class BlockS : public block {
    vector<vector<int>> off;
    bool isRandom = false;
    string colour;
    int level = 1;

public:
    virtual bool drop();
    virtual bool rotateClockwise();
    virtual bool rotateCounter();
    virtual bool moveRight();
    virtual bool moveLeft();
    virtual bool moveDown();
    virtual void reset();
};


#endif //BIQUAD_BLOCKS_H
