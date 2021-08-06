#ifndef PROJECTFILES_RAIILEVEL_H
#define PROJECTFILES_RAIILEVEL_H
#include "level4.h"
#include "level3.h"
#include "level1.h"
#include "level0.h"
#include "level2.h"
#include <memory>

using namespace std;
class error{};
class RAIILevel {
    vector<shared_ptr<generation>> l;
public:
    RAIILevel(string text);
    shared_ptr<generation> getLevel(int level);
};


#endif //PROJECTFILES_RAIILEVEL_H
