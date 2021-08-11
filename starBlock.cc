#include "starBlock.h"
#include <iostream>

using namespace std;

StarBlock::StarBlock(int level, vector<vector<int>> coord) : type{"*"}, temp{false}, level{ level }, coord{ coord } {}

string StarBlock::getType() const {
    return type;
}

bool StarBlock::isTemp() const {
    return temp;
}

void StarBlock::setTemp(bool state) {
    temp = state;
}

void StarBlock::setStage(int setTo) {
}

vector<vector<int>> StarBlock::getCoord() const {
    return coord;
}

vector<vector<int>> StarBlock::changeCoord(int diff, string axis) const {
    vector<vector<int>> newCoord;

    int x = coord[0][0];
    int y = coord[0][1] + 1;
    vector<int> pos = {x, y};
    newCoord.emplace_back(pos);

    return newCoord;
}

void StarBlock::removeCoord(int x, int y) {
    if (coord[0][0] == x && coord[0][1] == y) {
        coord[0][0] = -1;
        coord[0][1] = -1;
    }
}

int StarBlock::getActiveCoord() const {
    if (coord[0][0] == -1 && coord[0][0] == -1) {
        return 0;
    }

    return 1;
}

int StarBlock::getLevel() const {
    return level;
}

int StarBlock::getStage() const {
    return -1;
}

vector<vector<int>> StarBlock::rotatedCoords(string dir) {
    return coord;
}