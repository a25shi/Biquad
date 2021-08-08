#ifndef BIQUAD_GENERATION_H
#define BIQUAD_GENERATION_H
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>

class generation {
protected:
    bool isRandom = false;
    int index = 0;
    int level;
    std::string file;
    std::vector<char> blocks;
public:
    generation(int level, std::string file) : level{level}, file{file}{};
    int getLevel();
    void readFile();
    void swapRandom(bool random, std::string file);
    virtual char genBlock() = 0;
};


#endif //BIQUAD_GENERATION_H
