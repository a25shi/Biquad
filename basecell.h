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
        void changeCoord(int diff, string axis) override;
};

#endif
