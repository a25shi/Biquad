#ifndef _BOARD_H_
#define _BOARD_H_
#include <vector>
#include <iostream>
#include <string>
#include "cell.h"
#include "basecell.h"
#include "blockL.h"

using namespace std;

class Board {
    const int rows = 18;
    const int cols = 11;
    bool textOutput = true;
    bool isRandom;
    bool isBlind;
    bool isHeavy;
    int curLevel;
    vector< vector<Cell*> > grid;
    int rowsFull();
    bool checkSpecial(int rows);
    void removeRow(int rowNum);
    void updateScore(int addPoints);
    void reset();

public:
    Board();
    ~Board();
    string getVal(int x, int y);
    void next(string type);
    bool move(string dir);
    bool wipeTemp();
};

#endif //BIQUAD_BOARD_H
