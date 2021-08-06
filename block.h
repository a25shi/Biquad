#ifndef BIQUAD_BLOCK_H
#define BIQUAD_BLOCK_H
#include "decorator.h"

using namespace std;

class Cell;

class Block : public Decorator {
    int genLevel;
    string type;
    bool temp;
    vector<vector<int>> coord;
public:
    Block(Cell *component, string type, vector<vector<int>> coord, int level);
    string getType() const override;
    bool isTemp() const override;
    void setTemp(bool state) override;
    vector<vector<int>> getCoord() const override;
    void changeCoord(int diff, string axis) override;
    void removeCoord(int x, int y) override;
    int getActiveCoord() const override;
    int getLevel() const override;
};


#endif //BIQUAD_BLOCK_H
