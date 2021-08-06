#ifndef BIQUAD_BLOCKO_H
#define BIQUAD_BLOCKO_H
#include "decorator.h"

using namespace std;

class Cell;

class BlockO : public Decorator {
    string type;
    bool temp;
    vector<vector<int>> coord;
public:
    BlockO(Cell *component, vector<vector<int>> coord);
    string getType() const override;
    bool isTemp() const override;
    vector<vector<int>> getCoord() const override;
    void changeCoord(int diff, string axis) override;
};


#endif //BIQUAD_BLOCKO_H
