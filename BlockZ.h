//
// Created by allen on 8/4/2021.
//

#ifndef BIQUAD_BLOCKZ_H
#define BIQUAD_BLOCKZ_H
#include "block.h"

class BlockZ : public block {

public:
    virtual bool drop();
    virtual bool rotateClockwise();
    virtual bool rotateCounter();
    virtual bool moveRight();
    virtual bool moveLeft();
    virtual bool moveDown();
    virtual void reset();
};


#endif //BIQUAD_BLOCKZ_H
