#ifndef BIQUAD_LEVEL0_H
#define BIQUAD_LEVEL0_H
#include <string>
#include "generation.h"
#include <vector>
#include <fstream>
class level0 : public generation{
    std::string file;
    int index = 0;
    std::vector<char> blocks;

    void readFile();
public:
    level0(std::string file);
    char genBlock() override;
};


#endif //BIQUAD_LEVEL0_H
