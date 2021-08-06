#include "blockL.h"
#include <iostream>

BlockL::BlockL(Cell *component, vector<vector<int>> coord, int curLevel) : Block{component, "L", coord, curLevel} {}