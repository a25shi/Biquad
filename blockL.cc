#include "blockL.h"
#include <iostream>

BlockL::BlockL(Cell *component, vector<vector<int>> coord,
               int curLevel, vector<vector<int>> rotation, int stage) : Block{component, "L", coord, curLevel, rotation, stage} {}