#include "basecell.h"
using namespace std;

Basecell::Basecell() : type{"."}, temp{false} {}

string Basecell::getType() const {
    return type;
}

bool Basecell::isTemp() const {
    return temp;
}

void Basecell::setTemp(bool state) {
    temp = state;
}

void Basecell::setStage(int setTo) {
}

vector<vector<int>> Basecell::getCoord() const {
    vector<vector<int>> nothing;
    return nothing;
}

vector<vector<int>> Basecell::changeCoord(int diff, string axis) const {
    vector<vector<int>> nothing;
    return nothing;
}

void Basecell::removeCoord(int x, int y) {
}

int Basecell::getActiveCoord() const {
    return 1;
}

int Basecell::getLevel() const {
    return -1;
}

int Basecell::getStage() const {
    return -1;
}

vector<vector<int>> Basecell::rotatedCoords(string dir) {
    vector<vector<int>> nothing;
    return nothing;
}