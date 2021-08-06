#include "block.h"

using namespace std;

Block::Block(Cell *component, string type, vector<vector<int>> coord) : Decorator{component},
                                                             type{type},
                                                             temp{true},
                                                             coord{ coord } {}

string Block::getType() const {
    return type;
}

bool Block::isTemp() const {
    return temp;
}

vector<vector<int>> Block::getCoord() const {
    return coord;
}

void Block::changeCoord(int diff, string axis) {
    for (int y = 0; y < 4; y++) {
        if (axis == "x") {
            coord[y][0] = coord[y][0] + diff;
        } else {
            coord[y][1] = coord[y][1] + diff;
        }
    }
}