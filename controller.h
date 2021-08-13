#ifndef _PROJECTFILES_CONTROLLER_H
#define _PROJECTFILES_CONTROLLER_H
#include "board.h"
#include "RAIILevel.h"
#include "tetris_graphics.h"

class Controller {
    Board* p1;
    Board* p2;
    Board* cur;
    vector<Board*> boards = {p1, p2};
    bool player;
    bool applySpecial(bool p1On, bool p2On, bool caller);
    void displayWinner();
public:
    Controller(Board* p1, Board* p2);
    ~Controller();
    int play(string text1, string text2, int init, int gameNo, bool graphics);
};


#endif //_PROJECTFILES_CONTROLLER_H
