#ifndef BIQUAD_LEVEL0_H
#define BIQUAD_LEVEL0_H
#include <string>
#include "generation.h"

class level0 : public generation{
public:
    level0(std::string file);
    char genBlock() override;
};


#endif //BIQUAD_LEVEL0_H
