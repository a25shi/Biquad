#include "RAIILevel.h"

shared_ptr<generation> RAIILevel::getLevel(int level) {
    if (level >= 0 && level <= 4) {
        return l[level];
    }
    throw error{};
}

RAIILevel::RAIILevel(string text) {
    l.emplace_back(make_shared<level0>(text));
    l.emplace_back(make_shared<level1>());
    l.emplace_back(make_shared<level2>());
    l.emplace_back(make_shared<level3>());
    l.emplace_back(make_shared<level4>());
}

