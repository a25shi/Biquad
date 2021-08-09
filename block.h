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
    vector<vector<int>> rotation;
    int stage;
    
    public:
        Block(Cell *component, string type, vector<vector<int>> coord, int level, vector<vector<int>> rotation, int stage);
        string getType() const override;
        bool isTemp() const override;
        void setTemp(bool state) override;
        vector<vector<int>> getCoord() const override;
        vector<vector<int>> changeCoord(int diff, string axis) const override;
        void removeCoord(int x, int y) override;
        int getActiveCoord() const override;
        int getLevel() const override;
        int getStage() const override;
        void setStage(int setTo) override;
        vector<vector<int>> rotatedCoords(string dir) override;
};


#endif //BIQUAD_BLOCK_H
