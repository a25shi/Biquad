#include "blockO.h"

BlockO::BlockO(Cell *component, vector<vector<int>> coord) : Decorator{component},
                                                             type{"O"},
                                                             temp{true},
                                                             coord{ coord } {}

string BlockO::getType() const {
    return type;
}

bool BlockO::isTemp() const {
    return temp;
}

vector<vector<int>> BlockO::getCoord() const {
    return coord;
}

void BlockO::changeCoord(int diff, string axis) {
    for (int y = 0; y < 4; y++) {
        if (axis == "x") {
            coord[y][0] = coord[y][0] + diff;
        } else {
            coord[y][1] = coord[y][1] + diff;
        }
    }
}