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
    int score = 0;
    bool textOutput = true;
    bool isRandom;
    bool isBlind;
    bool isHeavy;
    int curLevel = 0;
    string nextBlock;

    vector< vector<Cell*> > grid;
    vector<vector<int>> curr;

    vector<int> rowsFull();
    bool checkSpecial(int rows);
    void removeRow(int rowNum);
    void wipeTemp();
    void reset();

public:
    Board();
    ~Board();
    string getVal(int x, int y);
    void next();
    bool move(string dir);
    void drop();
    int getScore();
    int getLevel();
    void setNext(string type);
    string getNext();

};

#endif //BIQUAD_BOARD_H
