#include <iomanip>
#include "controller.h"
#include "RAIILevel.h"
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

ostream &operator<<(ostream &out, vector<Board*> boards) {
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
                    }
                else {
                    out << boards[0]->getVal(x, y);
                }
            } else {
                out << boards[0]->getVal(x, y);
            }
        }

        out << setw(5)  << " ";

        bool b2Blind = boards[1]->getBlind();
        for (int i = 0; i < 11; i++) {
            if (b2Blind) {
                if (i >= 2 && i <= 8 &&
                    y >= 2 && y <= 12) {
                        out << "?";
                    }
                else {
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
                else boards[0]->setBlind(true);
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

void Controller::play(string text1, string text2, int init, int gameNo) {
    string cmd;

    RAIILevel p1level{text1};
    RAIILevel p2level{text2};
    shared_ptr<generation> l1 = p1level.getLevel(init);
    shared_ptr<generation> l2 = p2level.getLevel(init);

    vector<Board*> boards = {p1, p2};

    blockGen(*p1, l1.get(), false);
    blockGen(*p1, l1.get(), true);

    blockGen(*p2, l1.get(), false);
    blockGen(*p2, l1.get(), true);

    cout << boards << endl;
    bool p1On = true;
    bool p2On = true;
    bool gameOn = true;
    int p1Count = 0;
    int p2Count = 0;

    if (gameNo != 1) {
        cin >> cmd;
    }

    while (gameOn) {
        if (player == true) {
            cur = p1;
        }
        else {
            cur = p2;
        }
        if ((cur == p2 && p2On) ||
            (cur == p1 && p1On)) {
            if (cmd == "right") {
                cur->move("r");
                bool special = false;
                if (cur->getHeavy()) {
                    bool move1 = cur->move("d");
                    bool move2 = cur->move("d");
                    if (!(move1 && move2)) {
                        special = cur->drop();
                        cur->setHeavy(false);
                    }
                }
                cout << boards << endl;
                if (special) {
                    if (cur == p1) p1On = applySpecial(p1On, p2On, p1On);
                    else p2On = applySpecial(p1On, p2On, p2On);
                }
            } else if (cmd == "left") {
                cur->move("l");
                bool special = false;
                if (cur->getHeavy()) {
                    bool move1 = cur->move("d");
                    bool move2 = cur->move("d");
                    if (!(move1 && move2)) {
                        special = cur->drop();
                        cur->setHeavy(false);
                    }
                }
                cout << boards << endl;
                if (special) {
                    if (cur == p1) p1On = applySpecial(p1On, p2On, p1On);
                    else p2On = applySpecial(p1On, p2On, p2On);
                }
            } else if (cmd == "down") {
                cur->move("d");
                cout << boards << endl;
            } else if (cmd == "drop") {
                bool special = cur->drop();
                if (cur->getBlind()) {
                    cur->setBlind(false);
                }
                if (cur->getHeavy()) {
                    if (cur->getLevel() < 3) {
                        cur->setHeavy(false);
                    }
                }
                if (player == true) {
                    p1On = blockGen(*cur, l1.get(), true);
                }
                else {
                    p2On = blockGen(*cur, l2.get(), true);
                }
                cout << boards << endl;
                if (special) {
                    if (cur == p1) p1On = applySpecial(p1On, p2On, p1On);
                    else p2On = applySpecial(p1On, p2On, p2On);
                }
                player = !player;
            } else if (cmd == "levelup") {
                try {
                    int level = cur->getLevel();
                    if (player == true) {
                        l1 = p1level.getLevel(level + 1);
                    }
                    else {
                        l2 = p2level.getLevel(level + 1);
                    }
                    cur->setLevel(level + 1);
                    cout << boards << endl;
                }
                catch (error) {}
            } else if (cmd == "leveldown") {
                try {
                    int level = cur->getLevel();
                    if (player == true) {
                        l1 = p1level.getLevel(level - 1);
                    }
                    else {
                        l2 = p2level.getLevel(level - 1);
                    }
                    cur->setLevel(level - 1);
                    cout << boards << endl;
                }
                catch (error) {}
            } else if (cmd == "I" || cmd == "L" || cmd == "J" || cmd == "O" ||
                    cmd == "S" || cmd == "Z" || cmd == "T") {
                if (p1 == cur) p1On = cur->replaceCurr(cmd);
                else p2On = cur->replaceCurr(cmd);
                cout << boards << endl;
            } else if (cmd == "norandom") {

            } else if (cmd == "random") {

            } else if (cmd == "sequence") {

            } else if (cmd == "restart") {

            } else if (cmd == "clockwise") {
                cur->rotate("c");
                cout << boards << endl;
            } else if (cmd == "counterclockwise") {
                cur->rotate("cc");
                cout << boards << endl;
            }
            else {
                cout << "Invalid Argument!" << endl;
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
                cin >> cmd;
            }

        } else {
            player = !player;
        }
    }
}