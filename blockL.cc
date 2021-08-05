#include "blockL.h"
#include "cell.h"
#include <iostream>

using namespace std;

BlockL::BlockL(Cell *component, vector<vector<int>> coord) : Decorator{component}, 
                                                               type{"L"},
                                                               temp{true},
                                                               coord{ coord } {}

string BlockL::getType() const {
    //cout << "here too?" << endl;
    return type;
}

bool BlockL::isTemp() const {
    return temp;
}

vector<vector<int>> BlockL::getCoord() const {
    return coord;
}

void BlockL::changeCoord(int diff, string axis) {
    for (int y = 0; y < 4; y++) {
        if (axis == "x") {
            coord[y][0] = coord[y][0] + diff;
        } else {
            coord[y][1] = coord[y][1] + diff;
        }
    }
}