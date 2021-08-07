#include "board.h"
using namespace std;
void Board::setLevel(int level) {
    curLevel = level;
}
Board::Board() {
    for (int y = 0; y < rows; y++) {
        vector<Cell*> cell;
        grid.emplace_back(cell);
        for (int x = 0; x < cols; x++) {
            grid[y].emplace_back(new Basecell{});
        }
    }

    for (int i = 0; i < 4; i++) {
        vector<int> row = {-1,-1};
        curr.emplace_back(row);
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

void Board::wipeTemp() {
    for (int x = 0; x < 4; x++) {
        delete grid[curr[x][1]][curr[x][0]];
        grid[curr[x][1]][curr[x][0]] = new Basecell{};
    }
}

bool Board::move(string dir) {
    string type = grid[curr[0][1]][curr[0][0]]->getType();

    vector<vector<int>> newCoord;
    if (dir == "r") {
        for (int i = 0; i < 4; i++) {
            int new_x = curr[i][0] + 1;
            int y = curr[i][1];
            bool same = false;

            for (int m = 0; m < 4; m++) {
                if (curr[m][1] == y && curr[m][0] == new_x) {
                    same = true;
                    break;
                }
            }

            if (!same) {
                if (new_x > 10 || (grid[y][new_x]->getType() != ".")) {
                    return false;
                }
            }
        }
        grid[curr[0][1]][curr[0][0]]->changeCoord(1, "x");
        newCoord = grid[curr[0][1]][curr[0][0]]->getCoord();
    } else if (dir == "l") {
        for (int i = 0; i < 4; i++) {
            int new_x = curr[i][0] - 1;
            int y = curr[i][1];
            bool same = false;
            for (int m = 0; m < 4; m++) {
                if (curr[m][1] == y && curr[m][0] == new_x) {
                    same = true;
                    break;
                }
            }

            if (!same) {
                if (new_x < 0 || (grid[y][new_x]->getType() != ".")) {
                    return false;
                }
            }
        }
        grid[curr[0][1]][curr[0][0]]->changeCoord(-1, "x");
        newCoord = grid[curr[0][1]][curr[0][0]]->getCoord();
    } else {
         for (int i = 0; i < 4; i++) {
            int x = curr[i][0];
            int new_y = curr[i][1] - 1;
            bool same = false;

            for (int m = 0; m < 4; m++) {
                if (curr[m][0] == x && curr[m][1] == new_y) {
                    same = true;
                    break;
                }
            }

            if (!same) {
                if (new_y < 0 || (grid[new_y][x]->getType() != ".")) {
                    return false;
                }
            }
        }
        grid[curr[0][1]][curr[0][0]]->changeCoord(-1, "y");
        newCoord = grid[curr[0][1]][curr[0][0]]->getCoord();
    }

    int genLevel = grid[curr[0][1]][curr[0][0]]->getLevel();
    wipeTemp();
    
    for (int i = 0; i < 4; i++) {
        if (type == "L") {
            grid[newCoord[i][1]][newCoord[i][0]] = new BlockL(grid[newCoord[i][1]][newCoord[i][0]], newCoord, genLevel);
            grid[newCoord[i][1]][newCoord[i][0]] = new BlockL(grid[newCoord[i][1]][newCoord[i][0]], newCoord, genLevel);
        } else if (type == "O") {
            grid[newCoord[i][1]][newCoord[i][0]] = new BlockO(grid[newCoord[i][1]][newCoord[i][0]], newCoord, genLevel);
            grid[newCoord[i][1]][newCoord[i][0]] = new BlockO(grid[newCoord[i][1]][newCoord[i][0]], newCoord, genLevel);
        } else if (type == "J") {
            grid[newCoord[i][1]][newCoord[i][0]] = new BlockJ(grid[newCoord[i][1]][newCoord[i][0]], newCoord, genLevel);
            grid[newCoord[i][1]][newCoord[i][0]] = new BlockJ(grid[newCoord[i][1]][newCoord[i][0]], newCoord, genLevel);
        } else if (type == "T") {
            grid[newCoord[i][1]][newCoord[i][0]] = new BlockT(grid[newCoord[i][1]][newCoord[i][0]], newCoord, genLevel);
            grid[newCoord[i][1]][newCoord[i][0]] = new BlockT(grid[newCoord[i][1]][newCoord[i][0]], newCoord, genLevel);
        } else if (type == "Z") {
            grid[newCoord[i][1]][newCoord[i][0]] = new BlockZ(grid[newCoord[i][1]][newCoord[i][0]], newCoord, genLevel);
            grid[newCoord[i][1]][newCoord[i][0]] = new BlockZ(grid[newCoord[i][1]][newCoord[i][0]], newCoord, genLevel);
        } else if (type == "S") {
            grid[newCoord[i][1]][newCoord[i][0]] = new BlockS(grid[newCoord[i][1]][newCoord[i][0]], newCoord, genLevel);
            grid[newCoord[i][1]][newCoord[i][0]] = new BlockS(grid[newCoord[i][1]][newCoord[i][0]], newCoord, genLevel);
        } else if (type == "T") {
            grid[newCoord[i][1]][newCoord[i][0]] = new BlockT(grid[newCoord[i][1]][newCoord[i][0]], newCoord, genLevel);
            grid[newCoord[i][1]][newCoord[i][0]] = new BlockT(grid[newCoord[i][1]][newCoord[i][0]], newCoord, genLevel);
        } else if (type == "I") {
            grid[newCoord[i][1]][newCoord[i][0]] = new BlockI(grid[newCoord[i][1]][newCoord[i][0]], newCoord, genLevel);
            grid[newCoord[i][1]][newCoord[i][0]] = new BlockI(grid[newCoord[i][1]][newCoord[i][0]], newCoord, genLevel);
        }
    }

    for (int i = 0; i < 4; i++) {
        curr[i][0] = newCoord[i][0];
        curr[i][1] = newCoord[i][1];
    }
    return true;
}

void Board::next() {
    vector<vector<int>> coord;
    for (int x = 0; x < 4; x++) {
        vector<int> row;
        coord.emplace_back(row);
    }
    if (nextBlock == "L") {
        coord[0] = {0, 13};
        coord[1] = {1, 13};
        coord[2] = {2, 13};
        coord[3] = {2, 14};
        for (int i = 0; i < 4; i++) {
            grid[coord[i][1]][coord[i][0]] = new BlockL(grid[coord[i][1]][coord[i][0]], coord, curLevel);
            grid[coord[i][1]][coord[i][0]] = new BlockL(grid[coord[i][1]][coord[i][0]], coord, curLevel);
        }
    } else if (nextBlock == "J") {
        coord[0] = {0, 14};
        coord[1] = {0, 13};
        coord[2] = {1, 13};
        coord[3] = {2, 13};
        for (int i = 0; i < 4; i++) {
            grid[coord[i][1]][coord[i][0]] = new BlockJ(grid[coord[i][1]][coord[i][0]], coord, curLevel);
            grid[coord[i][1]][coord[i][0]] = new BlockJ(grid[coord[i][1]][coord[i][0]], coord, curLevel);
        }
    } else if (nextBlock == "O") {
        coord[0] = {0, 14};
        coord[1] = {0, 13};
        coord[2] = {1, 13};
        coord[3] = {1, 14};
        for (int i = 0; i < 4; i++) {
            grid[coord[i][1]][coord[i][0]] = new BlockO(grid[coord[i][1]][coord[i][0]], coord, curLevel);
            grid[coord[i][1]][coord[i][0]] = new BlockO(grid[coord[i][1]][coord[i][0]], coord, curLevel);
        }
    } else if (nextBlock == "Z") {
        coord[0] = {0, 14};
        coord[1] = {2, 13};
        coord[2] = {1, 13};
        coord[3] = {1, 14};
        for (int i = 0; i < 4; i++) {
            grid[coord[i][1]][coord[i][0]] = new BlockZ(grid[coord[i][1]][coord[i][0]], coord, curLevel);
            grid[coord[i][1]][coord[i][0]] = new BlockZ(grid[coord[i][1]][coord[i][0]], coord, curLevel);
        }
    } else if (nextBlock == "S") {
        coord[0] = {0, 13};
        coord[1] = {2, 14};
        coord[2] = {1, 13};
        coord[3] = {1, 14};
        for (int i = 0; i < 4; i++) {
            grid[coord[i][1]][coord[i][0]] = new BlockS(grid[coord[i][1]][coord[i][0]], coord, curLevel);
            grid[coord[i][1]][coord[i][0]] = new BlockS(grid[coord[i][1]][coord[i][0]], coord, curLevel);
        }
    } else if (nextBlock == "T") {
        coord[0] = {0, 14};
        coord[1] = {1, 14};
        coord[2] = {2, 14};
        coord[3] = {1, 13};
        for (int i = 0; i < 4; i++) {
            grid[coord[i][1]][coord[i][0]] = new BlockT(grid[coord[i][1]][coord[i][0]], coord, curLevel);
            grid[coord[i][1]][coord[i][0]] = new BlockT(grid[coord[i][1]][coord[i][0]], coord, curLevel);
        }
    } else if (nextBlock == "I") {
        coord[0] = {0, 14};
        coord[1] = {1, 14};
        coord[2] = {2, 14};
        coord[3] = {3, 14};
        for (int i = 0; i < 4; i++) {
            grid[coord[i][1]][coord[i][0]] = new BlockI(grid[coord[i][1]][coord[i][0]], coord, curLevel);
            grid[coord[i][1]][coord[i][0]] = new BlockI(grid[coord[i][1]][coord[i][0]], coord, curLevel);
        }
    } else {
        cout << "failure" << endl;
    }

    for (int i = 0; i < 4; i++) {
        curr[i][0] = coord[i][0];
        curr[i][1] = coord[i][1];
    }
}

vector<int> Board::rowsFull() {
    vector<int> fullRows;
    for (int y = 0; y < rows; y++) {
        bool rowFull = true;
        for (int x = 0; x < cols; x++) {
            if (grid[y][x]->getType() == ".") {
                rowFull = false;
                break;
            }
        }
        if (rowFull) {
            fullRows.emplace_back(y);
        }
    }

    return fullRows;
}

void Board::removeRow(int rowNum) {
    for (int x = 0; x < cols; x++) {
        int coordsLeft = grid[rowNum][x]->getActiveCoord();
        if (coordsLeft == 1) {
            int genLevel = grid[rowNum][x]->getLevel();
            int points = (genLevel + 1) * (genLevel + 1);
            score += points;
        }
        delete grid[rowNum][x];
    }

    for (int y = rowNum; y < rows - 1; y++) {
        for (int i = 0; i < cols; i++) {
            grid[y][i] = grid[y + 1][i];
        }
    }
}

void Board::drop() {
    for (int x = 0; x < 18; x++) {
        bool success = this->move("d");
    }

    for (int y = 0; y < 4; y++) {
        grid[curr[y][1]][curr[y][0]]->setTemp(false);
    }

    vector<int> emptyRow = rowsFull();
    for (int i = emptyRow.size() - 1; i >= 0; i--) {
        removeRow(emptyRow.at(i));
    }

    int points = (curLevel + emptyRow.size()) * (curLevel + emptyRow.size());
    score += points;
}

int Board::getScore() {
    return score;
}

int Board::getLevel() {
    return curLevel;
}

void Board::setNext(string type) {
    nextBlock = type;
}

string Board::getNext() {
    return nextBlock;
}

bool Board::replaceCurr(string type) {
    for (int x = 0; x < 4; x++) {
        delete grid[curr[x][1]][curr[x][0]];
        grid[curr[x][1]][curr[x][0]] = new Basecell{};
    }

    string temp = nextBlock;
    nextBlock = type;
    next();;
    setNext(temp);

    return true;
}