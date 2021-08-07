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
    vector<vector<int>> rotationL;
    vector<vector<int>> rotationO;
    vector<vector<int>> rotationS;
    vector<vector<int>> rotationZ;
    vector<vector<int>> rotationJ;
    vector<vector<int>> rotationT;
    vector<vector<int>> rotationI;

    vector< vector<Cell*> > grid;
    vector<vector<int>> curr;

    vector<int> rowsFull();
    bool checkSpecial(int rows);
    void removeRow(int rowNum);
    void wipeTemp();
    void reset();
    void resetCurr(vector<vector<int>> newCoord, string type, int genLevel, int stage);

public:
    Board();
    ~Board();
    string getVal(int x, int y) const;
    void next();
    bool move(string dir);
    void drop();
    int getScore() const;
    int getLevel() const;
    void setLevel(int level);
    void setNext(string type);
    bool replaceCurr(string type);
    string getNext() const;
    bool rotate(string dir);
    bool checkMove(vector<vector<int>> newCoord);
};

#endif //BIQUAD_BOARD_H
