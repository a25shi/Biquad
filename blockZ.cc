#include "blockZ.h"

BlockZ::BlockZ(Cell *component, vector<vector<int>> coord,
               int curLevel, vector<vector<int>> rotation, int stage) : Block{component, "Z", coord, curLevel, rotation, stage} {}