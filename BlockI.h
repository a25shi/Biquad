#ifndef BIQUAD_BLOCKI_H
#define BIQUAD_BLOCKI_H
#include "block.h"

#include "block.h"

class BlockI : public block {
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


#endif //BIQUAD_BLOCKI_H
