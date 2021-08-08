#ifndef _PROJECTFILES_CONTROLLER_H
#define _PROJECTFILES_CONTROLLER_H
#include "board.h"

class Controller {
    Board* p1;
    Board* p2;
    Board* cur;
    vector<Board*> boards = {p1, p2};
    bool player;
    bool applySpecial();
public:
    Controller(Board* p1, Board* p2);
    void play(string text1, string text2, int init);
};


#endif //_PROJECTFILES_CONTROLLER_H
