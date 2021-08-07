#include "blockT.h"

BlockT::BlockT(Cell *component, vector<vector<int>> coord,
               int curLevel, vector<vector<int>> rotation, int stage) : Block{component, "T", coord, curLevel, rotation, stage} {}