//
// Created by allen on 8/4/2021.
//

#ifndef BIQUAD_BLOCKJ_H
#define BIQUAD_BLOCKJ_H


#include "block.h"

class BlockJ : public block {

public:
    virtual bool drop();
    virtual bool rotateClockwise();
    virtual bool rotateCounter();
    virtual bool moveRight();
    virtual bool moveLeft();
    virtual bool moveDown();
    virtual void reset();
};

#endif //BIQUAD_BLOCKJ_H
