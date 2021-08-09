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
        virtual vector<vector<int>> changeCoord(int diff, string axis) const = 0;
        virtual void removeCoord(int x, int y) = 0;
        virtual int getActiveCoord() const = 0;
        virtual int getLevel() const = 0;
        virtual int getStage() const = 0;
        virtual void setStage(int setTo) = 0;
        virtual vector<vector<int>> rotatedCoords(string dir) = 0;
        virtual ~Cell();
};

#endif
