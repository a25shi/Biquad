#include "starBlock.h"
using namespace std;

StarBlock::StarBlock(int level) : type{"*"}, temp{false}, level{ level } {}

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
    vector<vector<int>> nothing;
    return nothing;
}

vector<vector<int>> StarBlock::changeCoord(int diff, string axis) const {
    vector<vector<int>> nothing;
    return nothing;
}

void StarBlock::removeCoord(int x, int y) {
}

int StarBlock::getActiveCoord() const {
    return 1;
}

int StarBlock::getLevel() const {
    return level;
}

int StarBlock::getStage() const {
    return -1;
}

vector<vector<int>> StarBlock::rotatedCoords(string dir) {
    vector<vector<int>> nothing;
    return nothing;
}