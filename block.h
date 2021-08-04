#ifndef BIQUAD_BLOCK_H
#define BIQUAD_BLOCK_H
#include <vector>
#include <string>
using namespace std;

class block {
    vector<vector<int>> off;
    bool isRandom = false;
    string colour;
    int level = 1;

public:
    virtual bool drop() = 0;
    virtual bool rotateClockwise() = 0;
    virtual bool rotateCounter() = 0;
    virtual bool moveRight() = 0;
    virtual bool moveLeft() = 0;
    virtual bool moveDown() = 0;
    virtual void reset() = 0;
};

#endif //BIQUAD_BLOCK_H
