#include "board.h"
using namespace std;

Board::Board() {
    for (int y = 0; y < rows; y++) {
        vector<Block*> blockRow;
        grid.emplace_back(blockRow);
        for (int x = 0; x < cols; x++) {
            grid[y].emplace_back(new Block{});
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

    for (int x = 0; x < 4; x++) {
        curr[x].clear();
    }
    curr.clear();
}

string Board::getVal(int x, int y) const {
    return grid[y][x]->getType();
}

bool Board::getBlind() const {
    return isBlind;
}

void Board::wipeTemp() {
    for (int x = 0; x < 4; x++) {
        delete grid[curr[x][1]][curr[x][0]];
        grid[curr[x][1]][curr[x][0]] = new Block{};
    }
}

vector<vector<int>> Board::getCurr() const {
    return curr;
}

string Board::getCurrType() const {
    return grid[curr[0][1]][curr[0][0]]->getType();
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

    if (nextBlock == "L") coord = {{0, 14}, {1, 14}, {2, 14}, {2, 15}};
    else if (nextBlock == "J") coord = {{0, 15}, {0, 14}, {1, 14}, {2, 14}};
    else if (nextBlock == "O") coord = {{0, 15}, {0, 14}, {1, 14}, {1, 15}};
    else if (nextBlock == "Z") coord = {{0, 15}, {1, 15}, {1, 14}, {2, 14}};
    else if (nextBlock == "S") coord = {{2, 15}, {1, 15}, {1, 14}, {0, 14}};
    else if (nextBlock == "T") coord = {{0, 15}, {1, 15}, {2, 15}, {1, 14}};
    else if (nextBlock == "I") coord = {{0, 14}, {1, 14}, {2, 14}, {3, 14}};

    if (!(checkMove(coord, false))) return false;

    for (int i = 0; i < 4; i++) {
        delete grid[coord[i][1]][coord[i][0]];
        grid[coord[i][1]][coord[i][0]] = new Block(nextBlock, coord, curLevel, 0);
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
        delete grid[newCoord[i][1]][newCoord[i][0]];
        grid[newCoord[i][1]][newCoord[i][0]] = new Block(type, newCoord, genLevel, stage);
    }

    for (int i = 0; i < 4; i++) {
        curr[i][0] = newCoord[i][0];
        curr[i][1] = newCoord[i][1];
    }
}

void Board::removeRow(int rowNum) {
    for (int x = 0; x < cols; x++) {
        vector<vector<int>> allCoord = grid[rowNum][x]->getCoord();
        if (grid[rowNum][x]->getType() == "*") {
            grid[rowNum][x]->removeCoord(x, rowNum);
        } else {
            for (int m = 0; m < 4; m++) {
                if (!(allCoord[m][1] == -1 && allCoord[m][0] == -1)) {
                    grid[allCoord[m][1]][allCoord[m][0]]->removeCoord(x, rowNum);
                }
            }
        }
        int coordsLeft = 0;
        if (grid[rowNum][x]->getType() != "*") coordsLeft = grid[rowNum][x]->getActiveCoord();
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
    
    for (int m = 0; m < cols; m++) {
        grid[rows - 1][m] = new Block{};
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

    if (curLevel == 4) {
        if (emptyRow.size() == 0) noDrops++;
        else noDrops = 0;

        if (noDrops == 5) {
            dropMiddle();
            noDrops = 0;
            
            emptyRow = rowsFull();
            for (int i = emptyRow.size() - 1; i >= 0; i--) {
                removeRow(emptyRow.at(i));
            }

            if (emptyRow.size() != 0) {
                int points = (curLevel + emptyRow.size()) * (curLevel + emptyRow.size());
                score += points;
            }
        }
    }

    if (emptyRow.size() >= 2) {
        return true;
    }

    return false;
}

void Board::dropMiddle() {
    int lowest = 18;
    for (int x = 17; x >= 0; x--) {
        if (grid[x][5]->getType() == ".") {
            lowest = x;
        } else {
            break;
        }
    }
    if (lowest != 18) {
        delete grid[lowest][5];

        vector<vector<int>> pos;
        vector<int> row = {5, lowest};
        pos.emplace_back(row);

        grid[lowest][5] = new Block{curLevel, pos};
    }
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
        grid[curr[x][1]][curr[x][0]] = new Block{};
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