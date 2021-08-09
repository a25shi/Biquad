#include "blockS.h"

BlockS::BlockS(Cell *component, vector<vector<int>> coord,
               int curLevel, vector<vector<int>> rotation, int stage) : Block{component, "S", coord, curLevel, rotation, stage} {}
