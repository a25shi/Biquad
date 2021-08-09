#include "blockI.h"

BlockI::BlockI(Cell *component, vector<vector<int>> coord,
               int curLevel, vector<vector<int>> rotation, int stage) : Block{component, "I", coord, curLevel, rotation, stage} {}