#ifndef BIQUAD_LEVEL4_H
#define BIQUAD_LEVEL4_H

#include "generation.h"

class level4 : public generation {
public:
    level4();
    char genBlock() override;
};


#endif //BIQUAD_LEVEL4_H
