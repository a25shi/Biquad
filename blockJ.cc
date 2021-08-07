#include "blockJ.h"

BlockJ::BlockJ(Cell *component, vector<vector<int>> coord,
               int curLevel, vector<vector<int>> rotation, int stage) : Block{component, "J", coord, curLevel, rotation, stage} {}