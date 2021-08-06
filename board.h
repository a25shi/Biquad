#ifndef _BOARD_H_
#define _BOARD_H_
#include <vector>
#include <iostream>
#include <string>
#include "cell.h"
#include "basecell.h"
#include "blockL.h"
#include "blockO.h"
#include "blockI.h"
#include "blockJ.h"
#include "blockZ.h"
#include "blockS.h"
#include "blockT.h"
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
    vector<vector<int>> curr;
    int rowsFull();
    bool checkSpecial(int rows);
    void removeRow(int rowNum);
    void updateScore(int addPoints);
    void wipeTemp();
    void reset();

public:
    Board();
    ~Board();
    string getVal(int x, int y);
    void next(string type);
    bool move(string dir);
    void drop();
};

#endif //BIQUAD_BOARD_H
