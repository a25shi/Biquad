#include <iomanip>
#include "controller.h"
#include "RAIILevel.h"
#include <sstream>
#include <fstream>

using namespace std;

Controller::Controller(Board *p1, Board *p2) : p1{p1}, p2{p2}, cur{p1}, player{true} {}

Controller::~Controller() {
    boards.clear();
}

bool blockGen(Board &b, generation *l, bool call) {
    char block = l->genBlock();
    string s(1, block);
    bool canPlace = true;
    if (call) {
        canPlace = b.next();
    }
    if (canPlace) {
        b.setNext(s);
    }

    return canPlace;
}

string getNextString(string type, int row) {
    if (type == "I") {
        if (row == 1) return "";
        return "IIII";
    } else if (type == "L") {
        if (row == 1) return "  L";
        return "LLL";
    } else if (type == "J") {
        if (row == 1) return "J";
        return "JJJ";
    } else if (type == "T") {
        if (row == 1) return "TTT";
        return " T";
    } else if (type == "S") {
        if (row == 1) return " SS";
        return "SS";
    } else if (type == "Z") {
        if (row == 1) return "ZZ";
        return " ZZ";
    }

    return "OO";
}

ostream &operator<<(ostream &out, vector<Board *> boards) {
    out << endl;

    out << " Player 1: ";
    out << right;
    out << setw(5) << " ";
    out << " Player 2: \n" << endl;

    out << "Level:";
    out << setw(5) << boards[0]->getLevel();
    out << setw(11) << "Level:";
    out << setw(5) << boards[1]->getLevel() << endl;

    out << "Score:";
    out << setw(5) << boards[0]->getScore();
    out << setw(11) << "Score:";
    out << setw(5) << boards[1]->getScore() << endl;

    out << string(11, '-');
    out << setw(5) << " ";
    out << string(11, '-') << endl;

    for (int y = 17; y >= 0; y--) {
        bool b1Blind = boards[0]->getBlind();
        for (int x = 0; x < 11; x++) {
            if (b1Blind) {
                if (x >= 2 && x <= 8 &&
                    y >= 2 && y <= 12) {
                    out << "?";
                } else {
                    out << boards[0]->getVal(x, y);
                }
            } else {
                //out << "here maybe" << endl;
                out << boards[0]->getVal(x, y);
                //out << "lets see" << endl;
            }
        }

        out << setw(5) << " ";

        bool b2Blind = boards[1]->getBlind();
        for (int i = 0; i < 11; i++) {
            if (b2Blind) {
                if (i >= 2 && i <= 8 &&
                    y >= 2 && y <= 12) {
                    out << "?";
                } else {
                    out << boards[1]->getVal(i, y);
                }
            } else {
                out << boards[1]->getVal(i, y);
            }
        }
        out << endl;
    }

    out << string(11, '-');
    out << setw(5) << " ";
    out << string(11, '-') << endl;

    out << "Next:";
    out << setw(11) << " ";
    out << "Next:" << endl;

    string type1 = boards[0]->getNext();
    string type2 = boards[1]->getNext();

    out << left;
    out << setw(16) << getNextString(type1, 1);
    out << getNextString(type2, 1) << endl;

    out << setw(16) << getNextString(type1, 2);
    out << getNextString(type2, 2) << endl;

    string nextType = boards[0]->getNext();

    return out;
}

void Controller::displayWinner() {
    int p1Points = boards[0]->getScore();
    int p2Points = boards[1]->getScore();

    cout << string(15, '-') << endl;
    cout << "Final Scores" << endl;
    cout << "Player 1:";
    cout << right;
    cout << setw(6) << p1Points << endl;
    cout << "Player 2:";
    cout << setw(6) << p2Points << endl;
    cout << endl;

    if (p1Points > p2Points) {
        cout << "Player 1 wins!" << endl;
    } else if (p1Points < p2Points) {
        cout << "Player 2 wins!" << endl;
    } else {
        cout << "It's a tie!" << endl;
    }
    cout << string(15, '-') << endl;
}

bool Controller::applySpecial(bool p1On, bool p2On, bool caller) {
    if (p1On && p2On) {
        cout << "Player ";
        if (player) cout << "1";
        cout << " has gained an advantage. Chose an action from the following: " << endl;
        cout << "- 'blind': turns the center of your opponents' board blind for the next turn" << endl;
        cout << "- 'heavy': turns your opponents' block heavy for the next turn" << endl;
        cout << "- 'force X': where X is a block type, which replaces your opponents current block" << endl;
        string specialEffect = "";
        cin >> specialEffect;
        bool done = true;

        while (true) {
            if (specialEffect == "blind") {
                if (player) boards[1]->setBlind(true);
                else boards[0]->setBlind(true);
                break;
            } else if (specialEffect == "heavy") {
                if (player) boards[1]->setHeavy(true);
                else boards[0]->setHeavy(true);
                break;
            } else if (specialEffect == "force") {
                string shape;
                cin >> shape;
                if (shape == "I" || shape == "L" || shape == "J" || shape == "O" ||
                    shape == "S" || shape == "Z" || shape == "T") {
                    if (player) done = boards[1]->replaceCurr(shape);
                    else done = boards[0]->replaceCurr(shape);
                    break;
                } else {
                    cout << "Invalid shape, try again!" << endl;
                }
            } else {
                cout << "Invalid command, try again!" << endl;
            }
            cin >> specialEffect;
        }

        cout << boards << endl;

        return done;
    }

    return caller;
}

int Controller::play(string text1, string text2, int init, int gameNo, bool graphics) {
    string cmd;

    RAIILevel p1level{text1};
    RAIILevel p2level{text2};
    shared_ptr<generation> l1 = p1level.getLevel(init);
    shared_ptr<generation> l2 = p2level.getLevel(init);

    vector<Board *> boards = {p1, p2};

    blockGen(*p1, l1.get(), false);
    blockGen(*p1, l1.get(), true);

    blockGen(*p2, l2.get(), false);
    blockGen(*p2, l2.get(), true);

    ifstream File;
    bool sequence = false;

    cout << boards << endl;
    bool p1On = true;
    bool p2On = true;
    bool gameOn = true;
    int p1Count = 0;
    int p2Count = 0;

    if (gameNo != 1) {
        cin >> cmd;
    }

    // initialize display
    Xwindow w;
    TetrisGraphics tg;

    vector<vector<int>> p1OldCurr = p1->getCurr();
    vector<vector<int>> p2OldCurr = p2->getCurr();

    if (graphics) {
        tg.player1_init(&w);
        tg.player2_init(&w);

        string p1type = p1->getCurrType();
        string p2type = p2->getCurrType();
        vector<vector<int>> p1init = p1->getCurr();
        vector<vector<int>> p2init = p2->getCurr();

        tg.display_block(&w, p1init, 1, p1type);
        tg.display_block(&w, p2init, 2, p2type);
    }

    while (gameOn) {
        if (player == true) {
            cur = p1;
        } else {
            cur = p2;
        }

        if ((cur == p2 && p2On) ||
            (cur == p1 && p1On)) {

            istringstream parse{cmd};
            int total = 1;
            if (!(parse >> total)) {
                parse.clear();
                total = 1;
            }
            parse >> cmd;
            if (cmd.substr(0,2) == "ri") {
                int curPlayer = 1;
                if (graphics) {
                    if (p2 == cur) {
                        curPlayer = 2;
                        p2OldCurr = cur->getCurr();
                        tg.erase_block(&w, p2OldCurr, curPlayer);
                    } else {
                        p1OldCurr = cur->getCurr();
                        tg.erase_block(&w, p1OldCurr, curPlayer);
                    }
                }

                for (int i = 0; i < total; i++) {
                    cur->move("r");
                }
                if (cur->getLevel() == 3 || cur->getLevel() == 4) {
                    cur->move("d");
                }
                bool special = false;
                if (cur->getHeavy()) {
                    bool move1 = cur->move("d");
                    bool move2 = cur->move("d");
                    if (!(move1 && move2)) {
                        special = cur->drop();
                        cur->setHeavy(false);
                        if (player == true) {
                            p1On = blockGen(*cur, l1.get(), true);
                        } else {
                            p2On = blockGen(*cur, l2.get(), true);
                        }
                        player = !player;
                    }
                }
                cout << boards << endl;

                if (graphics) {
                    vector<vector<int>> curPos = cur->getCurr();
                    string curType = cur->getCurrType();
                    tg.display_block(&w, curPos, curPlayer, curType);
                }

                if (special) {
                    if (cur == p1) p1On = applySpecial(p1On, p2On, p1On);
                    else p2On = applySpecial(p1On, p2On, p2On);
                }
            } else if (cmd.substr(0,3) == "lef") {
                int curPlayer = 1;
                if (graphics) {
                    if (p2 == cur) {
                        curPlayer = 2;
                        p2OldCurr = cur->getCurr();
                        tg.erase_block(&w, p2OldCurr, curPlayer);
                    } else {
                        p1OldCurr = cur->getCurr();
                        tg.erase_block(&w, p1OldCurr, curPlayer);
                    }
                }
                for (int i = 0; i < total; i++) {
                    cur->move("l");
                }
                if (cur->getLevel() == 3 || cur->getLevel() == 4) {
                    cur->move("d");
                }
                bool special = false;
                if (cur->getHeavy()) {
                    bool move1 = cur->move("d");
                    bool move2 = cur->move("d");
                    if (!(move1 && move2)) {
                        special = cur->drop();
                        cur->setHeavy(false);
                        if (player == true) {
                            p1On = blockGen(*cur, l1.get(), true);
                        } else {
                            p2On = blockGen(*cur, l2.get(), true);
                        }
                        player = !player;
                    }
                }
                cout << boards << endl;

                if (graphics) {
                    vector<vector<int>> curPos = cur->getCurr();
                    string curType = cur->getCurrType();
                    tg.display_block(&w, curPos, curPlayer, curType);
                }

                if (special) {
                    if (cur == p1) p1On = applySpecial(p1On, p2On, p1On);
                    else p2On = applySpecial(p1On, p2On, p2On);
                }
            } else if (cmd.substr(0,2) == "do") {
                int curPlayer = 1;
                if (graphics) {
                    if (p2 == cur) {
                        curPlayer = 2;
                        p2OldCurr = cur->getCurr();
                        tg.erase_block(&w, p2OldCurr, curPlayer);
                    } else {
                        p1OldCurr = cur->getCurr();
                        tg.erase_block(&w, p1OldCurr, curPlayer);
                    }
                }

                for (int i = 0; i < total; i++) {
                    cur->move("d");
                }
                if (cur->getLevel() == 3 || cur->getLevel() == 4) {
                    cur->move("d");
                }

                cout << boards << endl;

                if (graphics) {
                    vector<vector<int>> curPos = cur->getCurr();
                    string curType = cur->getCurrType();
                    tg.display_block(&w, curPos, curPlayer, curType);
                }

            } else if (cmd.substr(0,2) == "dr") {
                int curPlayer = 1;
                if (graphics) {
                    if (p2 == cur) {
                        curPlayer = 2;
                        p2OldCurr = cur->getCurr();
                        tg.erase_block(&w, p2OldCurr, curPlayer);
                    } else {
                        p1OldCurr = cur->getCurr();
                        tg.erase_block(&w, p1OldCurr, curPlayer);
                    }
                }
                bool special = false;
                for (int i = 0; i < total; i++) {
                    bool specialtemp = cur->drop();
                    if (special == false) {
                        special = specialtemp;
                    }
                    if (cur->getBlind()) {
                        cur->setBlind(false);
                    }
                    if (cur->getHeavy()) {
                        cur->setHeavy(false);
                    }

                    if (graphics) {
                        vector<vector<int>> curPos = cur->getCurr();
                        string curType = cur->getCurrType();
                        tg.display_block(&w, curPos, curPlayer, curType);
                    }

                    if (player == true) {
                        p1On = blockGen(*cur, l1.get(), true);
                    } else {
                        p2On = blockGen(*cur, l2.get(), true);
                    }
                }
                cout << boards << endl;

                if (graphics) {
                    vector<vector<int>> curPos = cur->getCurr();
                    string curType = cur->getCurrType();
                    tg.display_block(&w, curPos, curPlayer, curType);
                }

                if (special) {
                    if (cur == p1) p1On = applySpecial(p1On, p2On, p1On);
                    else p2On = applySpecial(p1On, p2On, p2On);
                }
                player = !player;
            } else if (cmd.substr(0,6) == "levelu") {
                int level = cur->getLevel();
                try {
                    for (int i = 0; i < total; i++) {
                        if (player == true) {
                            l1 = p1level.getLevel(level + 1);
                        } else {
                            l2 = p2level.getLevel(level + 1);
                        }
                        cur->setLevel(level + 1);
                    }
                }
                catch (error) {}
                cout << boards << endl;
            } else if (cmd.substr(0,6) == "leveld") {
                int level = cur->getLevel();
                try {
                    for (int i = 0; i < total; i++) {
                        if (player == true) {
                            l1 = p1level.getLevel(level - 1);
                        } else {
                            l2 = p2level.getLevel(level - 1);
                        }
                        cur->setLevel(level - 1);
                    }
                }
                catch (error) {}
                cout << boards << endl;
            } else if (cmd == "I" || cmd == "L" || cmd == "J" || cmd == "O" ||
                       cmd == "S" || cmd == "Z" || cmd == "T") {

                int curPlayer = 1;
                if (graphics) {
                    if (p2 == cur) {
                        curPlayer = 2;
                        p2OldCurr = cur->getCurr();
                        tg.erase_block(&w, p2OldCurr, curPlayer);
                    } else {
                        p1OldCurr = cur->getCurr();
                        tg.erase_block(&w, p1OldCurr, curPlayer);
                    }
                }

                if (p2 == cur) p2On = cur->replaceCurr(cmd);
                else p1On = cur->replaceCurr(cmd);

                cout << boards << endl;

                if (graphics) {
                    vector<vector<int>> curPos = cur->getCurr();
                    string curType = cur->getCurrType();
                    tg.display_block(&w, curPos, curPlayer, curType);
                }

            } else if (cmd.substr(0,5) == "noran") {
                if (cur == p1) {
                    p1level.swapRandom(true, "");
                } else {
                    p2level.swapRandom(true, "");
                }
            } else if (cmd.substr(0,3) == "ran") {
                string file;
                cin >> file;
                if (cur == p1) {
                    p1level.swapRandom(true, file);
                } else {
                    p2level.swapRandom(true, file);
                }
            } else if (cmd.substr(0,3) == "seq") {
                string file;
                cin >> file;
                File = ifstream (file);
                sequence = true;
            } else if (cmd.substr(0,3) == "res") {
                return 0;
            } else if (cmd.substr(0,2) == "cl") {
                int curPlayer = 1;
                if (graphics) {
                    if (p2 == cur) {
                        curPlayer = 2;
                        p2OldCurr = cur->getCurr();
                        tg.erase_block(&w, p2OldCurr, curPlayer);
                    } else {
                        p1OldCurr = cur->getCurr();
                        tg.erase_block(&w, p1OldCurr, curPlayer);
                    }
                }

                cur->rotate("c");
                if (cur->getLevel() == 3 || cur->getLevel() == 4) {
                    cur->move("d");
                }
                cout << boards << endl;

                if (graphics) {
                    vector<vector<int>> curPos = cur->getCurr();
                    string curType = cur->getCurrType();
                    tg.display_block(&w, curPos, curPlayer, curType);
                }
            } else if (cmd.substr(0,2) == "co") {
                int curPlayer = 1;
                if (graphics) {
                    if (p2 == cur) {
                        curPlayer = 2;
                        p2OldCurr = cur->getCurr();
                        tg.erase_block(&w, p2OldCurr, curPlayer);
                    } else {
                        p1OldCurr = cur->getCurr();
                        tg.erase_block(&w, p1OldCurr, curPlayer);
                    }
                }

                cur->rotate("cc");
                if (cur->getLevel() == 3 || cur->getLevel() == 4) {
                    cur->move("d");
                }

                cout << boards << endl;

                if (graphics) {
                    vector<vector<int>> curPos = cur->getCurr();
                    string curType = cur->getCurrType();
                    tg.display_block(&w, curPos, curPlayer, curType);
                }
            } else if (cmd == "quit") {
                return -1;
            } else {
                if (cmd != "") {
                    cout << "Invalid Argument!" << endl;
                }
            }
            if (cur == p1 && !p1On) {
                if (p1Count == 0) {
                    cout << "Player 1 has filled up their board :(" << endl;
                    p1Count++;
                }
            } else if (cur == p2 && !p2On) {
                if (p2Count == 0) {
                    cout << "Player 2 has filled up their board :(" << endl;
                    p2Count++;
                }
            }
            if (!p1On && !p2On) {
                displayWinner();
                gameOn = false;
            } else {
                if (sequence) {
                    if (!(File >> cmd)) {
                        sequence = false;
                        cin >> cmd;
                    }
                }
                else {
                    cin >> cmd;
                } 
            }
        } else {
            player = !player;
        }

        
    }
    return 1;
}

