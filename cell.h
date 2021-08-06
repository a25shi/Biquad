#ifndef _CELL_H_
#define _CELL_H_
#include <vector>
#include <string>

using namespace std;

class Cell {
    public:
        virtual string getType() const = 0;
        virtual bool isTemp() const = 0;
        virtual void setTemp(bool state) = 0;
        virtual vector<vector<int>> getCoord() const = 0;
        virtual void changeCoord(int diff, string axis) = 0;
        virtual ~Cell();
};

#endif
