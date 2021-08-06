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

vector<vector<int>> Basecell::getCoord() const {
    vector<vector<int>> nothing;
    return nothing;
}

void Basecell::changeCoord(int diff, string axis) {
}