#include "board.h"
using namespace std;

Board::Board() {
    for (int y = 0; y < rows; y++) {
        vector<Cell*> cell;
        grid.emplace_back(cell);
        for (int x = 0; x < cols; x++) {
            grid[y].emplace_back(new Basecell{});
        }
    }
}

Board::~Board() {
    for (int y = 0; y < rows; y++) {
        grid[y].clear();
    }
    grid.clear();
}

string Board::getVal(int x, int y) {
    return grid.at(y).at(x)->getType();
}

bool Board::wipeTemp() {
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols - 1; x++) {
            if (grid[y][x]->isTemp()) {
                delete grid[y][x];
                grid[y][x] = new Basecell{};
            }
        }
    }
    return true;
}

bool Board::move(string dir) {
    string type;
    bool success = false;
    bool cont = true;
    vector<vector<int>> newCoord;
    for (int y = 0; y < rows; y++) {
        if (cont) {
            for (int x = 0; x < cols - 1; x++) {
                if (grid[y][x]->isTemp()) {
                    type = grid[y][x]->getType();
                    if (dir == "r") {
                        grid[y][x]->changeCoord(1, "x");
                    } else if (dir == "l") {
                        grid[y][x]->changeCoord(-1, "x");
                    } else if (dir == "d") {
                        grid[y][x]->changeCoord(-1, "y");
                    }
                    newCoord = grid[y][x]->getCoord();
                    cont = false;
                    break;
                }
            }
        }
    }
    success = wipeTemp();
    for (int i = 0; i < 4; i++) {
        if (type == "L") {
            grid[newCoord[i][1]][newCoord[i][0]] = new BlockL(grid[newCoord[i][1]][newCoord[i][0]], newCoord);
            grid[newCoord[i][1]][newCoord[i][0]] = new BlockL(grid[newCoord[i][1]][newCoord[i][0]], newCoord);
        }
        else if (type == "O") {
            grid[newCoord[i][1]][newCoord[i][0]] = new BlockO(grid[newCoord[i][1]][newCoord[i][0]], newCoord);
            grid[newCoord[i][1]][newCoord[i][0]] = new BlockO(grid[newCoord[i][1]][newCoord[i][0]], newCoord);
        }
    }
    return success;
}

void Board::next(string type) {
    vector<vector<int>> coord;
    for (int x = 0; x < 4; x++) {
        vector<int> row;
        coord.emplace_back(row);
    }
    if (type == "L") {
        coord[0] = {0, 13};
        coord[1] = {1, 13};
        coord[2] = {2, 13};
        coord[3] = {2, 14};
        for (int i = 0; i < 4; i++) {
            grid[coord[i][1]][coord[i][0]] = new BlockL(grid[coord[i][1]][coord[i][0]], coord);
            grid[coord[i][1]][coord[i][0]] = new BlockL(grid[coord[i][1]][coord[i][0]], coord);
        }
    }
    if (type == "J") {
        coord[0] = {0, 14};
        coord[1] = {0, 13};
        coord[2] = {1, 13};
        coord[3] = {2, 13};
        for (int i = 0; i < 4; i++) {
            grid[coord[i][1]][coord[i][0]] = new BlockJ(grid[coord[i][1]][coord[i][0]], coord);
            grid[coord[i][1]][coord[i][0]] = new BlockJ(grid[coord[i][1]][coord[i][0]], coord);
        }
    }
    if (type == "O") {
        coord[0] = {0, 14};
        coord[1] = {0, 13};
        coord[2] = {1, 13};
        coord[3] = {1, 14};
        for (int i = 0; i < 4; i++) {
            grid[coord[i][1]][coord[i][0]] = new BlockO(grid[coord[i][1]][coord[i][0]], coord);
            grid[coord[i][1]][coord[i][0]] = new BlockO(grid[coord[i][1]][coord[i][0]], coord);
        }
    }
    if (type == "Z") {
        coord[0] = {0, 14};
        coord[1] = {2, 13};
        coord[2] = {1, 13};
        coord[3] = {1, 14};
        for (int i = 0; i < 4; i++) {
            grid[coord[i][1]][coord[i][0]] = new BlockZ(grid[coord[i][1]][coord[i][0]], coord);
            grid[coord[i][1]][coord[i][0]] = new BlockZ(grid[coord[i][1]][coord[i][0]], coord);
        }
    }
    if (type == "S") {
        coord[0] = {0, 13};
        coord[1] = {2, 14};
        coord[2] = {1, 13};
        coord[3] = {1, 14};
        for (int i = 0; i < 4; i++) {
            grid[coord[i][1]][coord[i][0]] = new BlockS(grid[coord[i][1]][coord[i][0]], coord);
            grid[coord[i][1]][coord[i][0]] = new BlockS(grid[coord[i][1]][coord[i][0]], coord);
        }
    }
    if (type == "T") {
        coord[0] = {0, 14};
        coord[1] = {1, 14};
        coord[2] = {2, 14};
        coord[3] = {1, 13};
        for (int i = 0; i < 4; i++) {
            grid[coord[i][1]][coord[i][0]] = new BlockT(grid[coord[i][1]][coord[i][0]], coord);
            grid[coord[i][1]][coord[i][0]] = new BlockT(grid[coord[i][1]][coord[i][0]], coord);
        }
    }
    if (type == "I") {
        coord[0] = {0, 14};
        coord[1] = {1, 14};
        coord[2] = {2, 14};
        coord[3] = {3, 14};
        for (int i = 0; i < 4; i++) {
            grid[coord[i][1]][coord[i][0]] = new BlockI(grid[coord[i][1]][coord[i][0]], coord);
            grid[coord[i][1]][coord[i][0]] = new BlockI(grid[coord[i][1]][coord[i][0]], coord);
        }
    }
}