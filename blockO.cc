#include "blockO.h"

BlockO::BlockO(Cell *component, vector<vector<int>> coord,
               int curLevel, vector<vector<int>> rotation, int stage) : Block{component, "O", coord, curLevel, rotation, stage} {}
