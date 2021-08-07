#ifndef PROJECTFILES_CONTROLLER_H
#define PROJECTFILES_CONTROLLER_H
#include "board.h"

class controller {
    Board* p1;
    Board* p2;
    Board* cur;
    bool player;
public:
    controller(Board* p1, Board* p2);
    void play(string text1, string text2, int init);
};


#endif //PROJECTFILES_CONTROLLER_H
