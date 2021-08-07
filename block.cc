#include "block.h"
#include <iostream>
using namespace std;

Block::Block(Cell *component, string type, vector<vector<int>> coord, int level) : Decorator{component},
                                                             type{type},
                                                             temp{true},
                                                             coord{ coord },
                                                             genLevel{ level } {}

string Block::getType() const {
    return type;
}

bool Block::isTemp() const {
    return temp;
}

void Block::setTemp(bool state) {
    temp = state;
}

vector<vector<int>> Block::getCoord() const {
    return coord;
}

void Block::changeCoord(int diff, string axis) {
    for (int y = 0; y < coord.size(); y++) {
        if (axis == "x") {
            coord[y][0] = coord[y][0] + diff;
        } else {
            coord[y][1] = coord[y][1] + diff;
        }
    }
}

void Block::removeCoord(int x, int y) {
    int pos = -1;
    for (int i = 0; i < coord.size(); i++) {
        if (coord[i][0] == x && coord[i][1] == y) {
            coord[i][0] = -1;
            coord[i][1] = -1;
            pos = i;
            break;
        }
    }
}

int Block::getActiveCoord() const {
    int counter = 0;
    for (int i = 0; i < coord.size(); i++) {
        if (!(coord[i][0] == -1 && coord[i][1] == -1)) {
            counter++;
        }
    }

    return counter;
}

int Block::getLevel() const {
    return genLevel;
}