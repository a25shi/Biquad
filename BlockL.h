//
// Created by allen on 8/4/2021.
//

#ifndef BIQUAD_BLOCKL_H
#define BIQUAD_BLOCKL_H


#include "block.h"

class BlockL : public block {
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


#endif //BIQUAD_BLOCKL_H
