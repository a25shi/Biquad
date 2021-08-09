#ifndef BIQUAD_LEVEL2_H
#define BIQUAD_LEVEL2_H
#include "generation.h"

class level2 : public generation{
public:
    level2();
    char genBlock() override;
};


#endif //BIQUAD_LEVEL2_H
