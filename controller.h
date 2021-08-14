#ifndef _PROJECTFILES_CONTROLLER_H
#define _PROJECTFILES_CONTROLLER_H
#include "board.h"
#include "window.h"
#include "tetris_graphics.h"

class Controller {
    Board* p1;
    Board* p2;
    Board* cur;
    vector<Board*> boards = {p1, p2};
    vector<string> commands = {"ri", "lef", "do", "dr", "levelu", "leveld", "noran", "ran", "seq", "res", "cl", "co", "ren"};
    bool player;
    bool applySpecial(bool p1On, bool p2On, bool caller);
    void displayWinner();
    void changeCommand();
public:
    Controller(Board* p1, Board* p2);
    ~Controller();
    int play(string text1, string text2, int init, int gameNo, bool graphics);
};


#endif //_PROJECTFILES_CONTROLLER_H
