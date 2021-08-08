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

    for (int i = 0; i < 4; i++) {
        vector<int> row = {-1,-1};
        curr.emplace_back(row);
    }

    rotationL = {{0, 2, -1, 1, -2, 0, -1, -1}, {2, 0, 1, 1, 0, 2, -1, 1}, 
                 {0, -2, 1, -1, 2, 0, 1, 1}, {-2, 0, -1, -1, 0, -2, 1, -1}};
    rotationO = {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, 
                 {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}};
    rotationJ = {{1, 1, 0, 2, -1, 1, -2, 0}, {1, -1, 2, 0, 1, 1, 0, 2},
                 {-1, -1, 0, -2, 1, -1, 2, 0}, {-1, 1, -2, 0, -1, -1, 0, -2}};
    rotationT = {{1, 1, 0, 0, -1, -1, -1, 1}, {1, -1, 0, 0, -1, 1, 1, 1},
                 {-1, -1, 0, 0, 1, 1, 1, -1}, {-1, 1, 0, 0, 1, -1, -1, -1}};
    rotationZ = {{1, 1, 0, 0, -1, 1, -2, 0}, {1, -2, 0, 0, 1, -1, 0, 1},
                 {-2, 0, 0, 0, -1, 1, 1, 1}, {0, 1, 0, 0, 1, -1, 1, -2}};
    rotationS = {{-1, -1, 0, 0, -1, 1, 0, 2}, {-1, 0, 0, 0, 1, -1, 2, -1},
                 {0, 2, 0, 0, -1, 1, -1, -1}, {2, -1, 0, 0, 1, -1, -1, 0}};
    rotationI = {{1, 2, 0, 1, -1, 0, -2, -1}, {2, -1, 1, 0, 0, 1, -1, 2},
                 {-1, -2, 0, -1, 1, 0, 2, 1}, {-2, 1, -1, 0, 0, -1, 1, -2}};
}

Board::~Board() {
    for (int y = 0; y < rows; y++) {
        grid[y].clear();
    }
    grid.clear();

    for (int x = 0; x < 4; x++) {
        curr[x].clear();
        rotationL[x].clear();
        rotationO[x].clear();
        rotationS[x].clear();
        rotationJ[x].clear();
        rotationT[x].clear();
        rotationZ[x].clear();
        rotationI[x].clear();
    }
    curr.clear();
    rotationL.clear();
    rotationO.clear();
    rotationS.clear();
    rotationJ.clear();
    rotationT.clear();
    rotationZ.clear();
    rotationI.clear();
}

string Board::getVal(int x, int y) const {
    return grid.at(y).at(x)->getType();
}

bool Board::getBlind() const {
    return isBlind;
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
        newCoord = grid[curr[0][1]][curr[0][0]]->changeCoord(1, "x");
    } else if (dir == "l") {
        newCoord = grid[curr[0][1]][curr[0][0]]->changeCoord(-1, "x");
    } else {
        newCoord = grid[curr[0][1]][curr[0][0]]->changeCoord(-1, "y");
    }

    if (!(checkMove(newCoord, true))) {
        return false;
    }

    int genLevel = grid[curr[0][1]][curr[0][0]]->getLevel();
    int stage = grid[curr[0][1]][curr[0][0]]->getStage();
    wipeTemp();
    resetCurr(newCoord, type, genLevel, stage);

    return true;
}

bool Board::next() {
    vector<vector<int>> coord;
    for (int x = 0; x < 4; x++) {
        vector<int> row;
        coord.emplace_back(row);
    }

    if (nextBlock == "L") {
        coord = {{0, 13}, {1, 13}, {2, 13}, {2, 14}};
        if (!(checkMove(coord, false))) return false;
        for (int i = 0; i < 4; i++) {
            grid[coord[i][1]][coord[i][0]] = new BlockL(grid[coord[i][1]][coord[i][0]], coord, curLevel, rotationL, 0);
        }
    } else if (nextBlock == "J") {
        coord = {{0, 14}, {0, 13}, {1, 13}, {2, 13}};
        if (!(checkMove(coord, false))) return false;
        for (int i = 0; i < 4; i++) {
            grid[coord[i][1]][coord[i][0]] = new BlockJ(grid[coord[i][1]][coord[i][0]], coord, curLevel, rotationJ, 0);
        }
    } else if (nextBlock == "O") {
        coord = {{0, 14}, {0, 13}, {1, 13}, {1, 14}};
        if (!(checkMove(coord, false))) return false;
        for (int i = 0; i < 4; i++) {
            grid[coord[i][1]][coord[i][0]] = new BlockO(grid[coord[i][1]][coord[i][0]], coord, curLevel, rotationO, 0);
        }
    } else if (nextBlock == "Z") {
        coord = {{0, 14}, {1, 14}, {1, 13}, {2, 13}};
        if (!(checkMove(coord, false))) return false;
        for (int i = 0; i < 4; i++) {
            grid[coord[i][1]][coord[i][0]] = new BlockZ(grid[coord[i][1]][coord[i][0]], coord, curLevel, rotationZ, 0);
        }
    } else if (nextBlock == "S") {
        coord = {{2, 14}, {1, 14}, {1, 13}, {0, 13}};
        if (!(checkMove(coord, false))) return false;
        for (int i = 0; i < 4; i++) {
            grid[coord[i][1]][coord[i][0]] = new BlockS(grid[coord[i][1]][coord[i][0]], coord, curLevel, rotationS, 0);
        }
    } else if (nextBlock == "T") {
        coord = {{0, 14}, {1, 14}, {2, 14}, {1, 13}};
        if (!(checkMove(coord, false))) return false;
        for (int i = 0; i < 4; i++) {
            grid[coord[i][1]][coord[i][0]] = new BlockT(grid[coord[i][1]][coord[i][0]], coord, curLevel, rotationT, 0);
        }
    } else if (nextBlock == "I") {
        coord = {{0, 14}, {1, 14}, {2, 14}, {3, 14}};
        if (!(checkMove(coord, false))) return false;
        for (int i = 0; i < 4; i++) {
            grid[coord[i][1]][coord[i][0]] = new BlockI(grid[coord[i][1]][coord[i][0]], coord, curLevel, rotationI, 0);
        }
    }

    for (int i = 0; i < 4; i++) {
        curr[i][0] = coord[i][0];
        curr[i][1] = coord[i][1];
    }

    return true;
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

void Board::resetCurr(vector<vector<int>> newCoord, string type, int genLevel, int stage) {
    for (int i = 0; i < 4; i++) {
        if (type == "L") {
            grid[newCoord[i][1]][newCoord[i][0]] = new BlockL(grid[newCoord[i][1]][newCoord[i][0]], newCoord, genLevel, rotationL, stage);
        } else if (type == "O") {
            grid[newCoord[i][1]][newCoord[i][0]] = new BlockO(grid[newCoord[i][1]][newCoord[i][0]], newCoord, genLevel, rotationO, stage);
        } else if (type == "J") {
            grid[newCoord[i][1]][newCoord[i][0]] = new BlockJ(grid[newCoord[i][1]][newCoord[i][0]], newCoord, genLevel, rotationJ, stage);
        } else if (type == "T") {
            grid[newCoord[i][1]][newCoord[i][0]] = new BlockT(grid[newCoord[i][1]][newCoord[i][0]], newCoord, genLevel, rotationT, stage);
        } else if (type == "Z") {
            grid[newCoord[i][1]][newCoord[i][0]] = new BlockZ(grid[newCoord[i][1]][newCoord[i][0]], newCoord, genLevel, rotationZ, stage);
        } else if (type == "S") {
            grid[newCoord[i][1]][newCoord[i][0]] = new BlockS(grid[newCoord[i][1]][newCoord[i][0]], newCoord, genLevel, rotationS, stage);
        } else {
            grid[newCoord[i][1]][newCoord[i][0]] = new BlockI(grid[newCoord[i][1]][newCoord[i][0]], newCoord, genLevel, rotationI, stage);
        }
    }

    for (int i = 0; i < 4; i++) {
        curr[i][0] = newCoord[i][0];
        curr[i][1] = newCoord[i][1];
    }
}

void Board::removeRow(int rowNum) {
    for (int x = 0; x < cols; x++) {
        vector<vector<int>> allCoord = grid[rowNum][x]->getCoord();
        for (int m = 0; m < 4; m++) {
            if (!(allCoord[m][1] == -1 && allCoord[m][0] == -1)) {
                grid[allCoord[m][1]][allCoord[m][0]]->removeCoord(x, rowNum);
            }
        }
        int coordsLeft = grid[rowNum][x]->getActiveCoord();
        if (coordsLeft == 0) {
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

bool Board::drop() {
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

    if (emptyRow.size() != 0) {
        int points = (curLevel + emptyRow.size()) * (curLevel + emptyRow.size());
        score += points;
    }

    if (emptyRow.size() >= 2) {
        return true;
    }

    return false;
}

int Board::getScore() const {
    return score;
}

int Board::getLevel() const {
    return curLevel;
}

void Board::setNext(string type) {
    nextBlock = type;
}

void Board::setLevel(int level) {
    curLevel = level;
    if (level >= 3) {
        this->setHeavy(true);
    }
}

string Board::getNext() const {
    return nextBlock;
}

bool Board::checkMove(vector<vector<int>> newCoord, bool checkCurr) const {
    for (int x = 0; x < 4; x++) {
        if (newCoord[x][0] < 0 || newCoord[x][0] > 10) {
            return false;
        } else if (newCoord[x][1] < 0 || newCoord[x][1] > 17) {
            return false;
        } else if (grid[newCoord[x][1]][newCoord[x][0]]->getType() != ".") {
            if (checkCurr) {
                bool blocking = true;
                for (int y = 0; y < 4; y++) {
                    if (newCoord[x][0] == curr[y][0] && newCoord[x][1] == curr[y][1]) {
                        blocking = false;
                        break;
                    }
                }
                if (blocking) {
                    return false;
                }
            } else {
                return false;
            }
        }
    }

    return true;
}

void Board::setBlind(bool state) {
    isBlind = state;
}

void Board::setHeavy(bool state) {
    isHeavy = state;
}

bool Board::getHeavy() const {
    return isHeavy;
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

void Board::rotate(string dir) {
    vector<vector<int>> rotatedCoord;
    int oldStage = grid[curr[0][1]][curr[0][0]]->getStage();
    if (dir == "c") {
        // clockwise
        rotatedCoord = grid[curr[0][1]][curr[0][0]]->rotatedCoords("c");
    } else {
        rotatedCoord = grid[curr[0][1]][curr[0][0]]->rotatedCoords("cc");
    }

    if (!(checkMove(rotatedCoord, true))) {
        grid[curr[0][1]][curr[0][0]]->setStage(oldStage);
        return;
    }

    string type = grid[curr[0][1]][curr[0][0]]->getType();
    int genLevel = grid[curr[0][1]][curr[0][0]]->getLevel();
    int stage = grid[curr[0][1]][curr[0][0]]->getStage();
    wipeTemp();
    resetCurr(rotatedCoord, type, genLevel, stage);
}