#ifndef _STAR_BLOCK_H_
#define _STAR_BLOCK_H_
#include "cell.h"

using namespace std;

class StarBlock : public Cell {
    string type;
    bool temp;
    int level;
    public:
        StarBlock(int level);
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

#endif
