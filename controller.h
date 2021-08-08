#ifndef _PROJECTFILES_CONTROLLER_H
#define _PROJECTFILES_CONTROLLER_H
#include "board.h"

class Controller {
    Board* p1;
    Board* p2;
    Board* cur;
    bool player;
public:
    Controller(Board* p1, Board* p2);
    void play(string text1, string text2, int init);
};


#endif //_PROJECTFILES_CONTROLLER_H
