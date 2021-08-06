#ifndef BIQUAD_BLOCK_H
#define BIQUAD_BLOCK_H
#include "decorator.h"

using namespace std;

class Cell;

class Block : public Decorator {
    string type;
    bool temp;
    vector<vector<int>> coord;
public:
    Block(Cell *component, string type, vector<vector<int>> coord);
    string getType() const override;
    bool isTemp() const override;
    vector<vector<int>> getCoord() const override;
    void changeCoord(int diff, string axis) override;
};


#endif //BIQUAD_BLOCK_H
