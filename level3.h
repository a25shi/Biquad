#ifndef BIQUAD_LEVEL3_H
#define BIQUAD_LEVEL3_H
#include "generation.h"

class level3 : public generation{
public:
    level3();
    char genBlock() override;
};


#endif //BIQUAD_LEVEL3_H
