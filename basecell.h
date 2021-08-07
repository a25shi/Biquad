#ifndef _BASECELL_H_
#define _BASECELL_H_
#include "cell.h"

using namespace std;

class Basecell : public Cell {
    string type;
    bool temp;
    public:
        Basecell();
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
