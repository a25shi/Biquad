#ifndef BIQUAD_GENERATION_H
#define BIQUAD_GENERATION_H
#include <cstdlib>

class generation {
    int level;
public:
    generation(int level);
    virtual char genBlock() = 0;
};


#endif //BIQUAD_GENERATION_H
