#ifndef BIQUAD_BOARD_H
#define BIQUAD_BOARD_H
#include <vector>
#include "block.h"

class board {
    bool textOutput = true;
    bool isRandom;
    bool isBlind;
    bool isHeavy;
    int curLevel;
    block* curr;
    block* next;
    vector<vector<int>> grid;

public:
    block* findBLock(int x, int y);
    block* nextBlock();
    block* nextBlockText(char type);
    int rowsFull();
    bool checkSpecial(int rows);
    void changeCur (block* nextOne);
    void removeRow(int rowNum);
    void updateScore(int addPoints);
    void reset();
};


#endif //BIQUAD_BOARD_H
