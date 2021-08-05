#ifndef BIQUAD_LEVEL1_H
#define BIQUAD_LEVEL1_H
#include "generation.h"

class level1 : public generation {
public:
    level1();
    char genBlock() override;
};


#endif //BIQUAD_LEVEL1_H
