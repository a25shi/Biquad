#include "block.h"
using namespace std;

Block::Block() : type{ "." }, temp{ false } {}

Block::Block(int level, vector<vector<int>> coord) : type{ "*"}, temp{ false }, genLevel{ level }, coord{ coord } {}

Block::Block(string type, vector<vector<int>> coord, int level, int stage) : type{type},
                                                                             temp{true},
                                                                             coord{ coord },
                                                                             genLevel{ level },
                                                                             stage{ stage } {
            if (type == "L") {
                rotation = {{0, 2, -1, 1, -2, 0, -1, -1}, {2, 0, 1, 1, 0, 2, -1, 1}, 
                            {0, -2, 1, -1, 2, 0, 1, 1}, {-2, 0, -1, -1, 0, -2, 1, -1}};
            } else if (type == "O") {
                rotation = {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, 
                            {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}};
            } else if (type == "J") {
                rotation = {{1, 1, 0, 2, -1, 1, -2, 0}, {1, -1, 2, 0, 1, 1, 0, 2},
                            {-1, -1, 0, -2, 1, -1, 2, 0}, {-1, 1, -2, 0, -1, -1, 0, -2}};
            } else if (type == "T") {
                rotation = {{1, 1, 0, 0, -1, -1, -1, 1}, {1, -1, 0, 0, -1, 1, 1, 1},
                            {-1, -1, 0, 0, 1, 1, 1, -1}, {-1, 1, 0, 0, 1, -1, -1, -1}};
            } else if (type == "S") {
                rotation = {{-1, -1, 0, 0, -1, 1, 0, 2}, {-1, 0, 0, 0, 1, -1, 2, -1},
                            {0, 2, 0, 0, -1, 1, -1, -1}, {2, -1, 0, 0, 1, -1, -1, 0}};
            } else if (type == "Z") {
                rotation = {{1, 1, 0, 0, -1, 1, -2, 0}, {1, -2, 0, 0, 1, -1, 0, 1},
                            {-2, 0, 0, 0, -1, 1, 1, 1}, {0, 1, 0, 0, 1, -1, 1, -2}};
            } else if (type == "I") {
                rotation = {{1, 3, 0, 2, -1, 1, -2, 0}, {-1, -3, 0, -2, 1, -1, 2, 0},
                            {1, 3, 0, 2, -1, 1, -2, 0}, {-1, -3, 0, -2, 1, -1, 2, 0}};
            }           
}

Block::~Block() {
   //2cout << "trying to delete" << endl;
    for (int x = 0; x < 4; x++) {
        if (rotation.size() != 0) {
            rotation[x].clear();
        }
        //2cout << "rot or cord" << endl;
        //2cout << "cord size: " << coord.size() << endl;
        if (coord.size() != 0 && type != "*") {
            coord[x].clear();
        }
        //2cout << "deleted " << x << endl;
    }
    if (type == "*") coord[0].clear();
    rotation.clear();
    coord.clear();
    //2cout << "deleted" << endl;
}

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

vector<vector<int>>  Block::changeCoord(int diff, string axis) const {
    vector<vector<int>> newCoord;
    for (int y = 0; y < coord.size(); y++) {
        vector<int> row;
        newCoord.emplace_back(row);
        if (axis == "x") {
            newCoord[y].emplace_back(coord[y][0] + diff);
            newCoord[y].emplace_back(coord[y][1]);
        } else {
            newCoord[y].emplace_back(coord[y][0]);
            newCoord[y].emplace_back(coord[y][1] + diff);
        }
    }

    return newCoord;
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

int Block::getStage() const {
    return stage;
}

void Block::setStage(int setTo) {
    stage = setTo;
}

vector<vector<int>> Block::rotatedCoords(string dir) {
    int factor = 1;
    if (dir == "cc") {
        factor = -1;
        stage--;
        if (stage < 0) stage = 3;
    }

    vector<vector<int>> newCoord;
    for (int x = 0; x < 4; x++) {
        vector<int> row;
        newCoord.emplace_back(row);
        int new_x = coord[x][0] + (factor * rotation[stage][x * 2]);
        int new_y = coord[x][1] + (factor * rotation[stage][(x * 2) + 1]);
        newCoord[x] = {new_x, new_y};
    }
    
    if (dir == "c") {
        stage++;
    }

    if (stage >= 4) {
        stage = 0;
    }

    return newCoord;
}