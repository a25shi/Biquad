#include "block.h"
#include <iostream>
using namespace std;

Block::Block(Cell *component, string type, vector<vector<int>> coord, 
             int level, vector<vector<int>> rotation, int stage) : Decorator{component},
                                                                type{type},
                                                                temp{true},
                                                                coord{ coord },
                                                                genLevel{ level },
                                                                rotation{ rotation },
                                                                stage{ stage } {}

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