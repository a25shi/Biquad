#ifndef _BLOCK_L_H_
#define _BLOCK_L_H_
#include "decorator.h"
#include <vector>
#include <string>

using namespace std;

class Cell;

class BlockL : public Decorator {
    string type;
    bool temp;
    vector<vector<int>> coord;
    public:
        BlockL(Cell *component, vector<vector<int>> coord);
        string getType() const override;
        bool isTemp() const override;
        vector<vector<int>> getCoord() const override;
        void changeCoord(int diff, string axis) override;
};

#endif
