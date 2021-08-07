#include <iomanip>
#include "controller.h"
#include "RAIILevel.h"
using namespace std;
controller::controller(Board *p1, Board *p2) : p1{p1}, p2{p2}, cur{p1}, player{true}{}

void blockGen(Board &b, generation *l, bool call) {
    char block = l->genBlock();
    string s(1, block);
    if (call) {
        b.next();
    }
    b.setNext(s);
}

ostream &operator<<(ostream &out, Board &b) {
    out << endl;
    out << "Level:";
    out << right;
    out << setw(5) << b.getLevel() << endl;

    out << "Score:";
    out << right;
    out << setw(5) << b.getScore() << endl;

    out << string(11, '-') << endl;
    for (int y = 17; y >= 0; y--) {
        for (int x = 0; x < 11; x++) {
            out << b.getVal(x, y);
        }
        out << endl;
    }
    out << string(11, '-') << endl;

    out << "Next:" << endl;
    string nextType = b.getNext();
    if (nextType == "O") {
        out << "OO" << endl;
        out << "OO" << endl;
    } else if (nextType == "L") {
        out << "  L" << endl;
        out << "LLL" << endl;
    } else if (nextType == "J") {
        out << "J" << endl;
        out << "JJJ" << endl;
    } else if (nextType == "T") {
        out << "TTT" << endl;
        out << " T" << endl;
    } else if (nextType == "S") {
        out << " SS" << endl;
        out << "SS" << endl;
    } else if (nextType == "Z") {
        out << "ZZ" << endl;
        out << " ZZ" << endl;
    } else {
        out << "IIII" << endl;
    }
    return out;
}

void controller::play(string text1, string text2, int init) {
    string cmd;

    RAIILevel p1level{text1};
    RAIILevel p2level{text2};
    shared_ptr<generation> l1 = p1level.getLevel(init);
    shared_ptr<generation> l2 = p2level.getLevel(init);

    blockGen(*p1, l1.get(), false);
    blockGen(*p1, l1.get(), true);

    blockGen(*p2, l1.get(), false);
    blockGen(*p2, l1.get(), true);

    while (cin >> cmd) {
        if (player == true) {
            cur = p1;
        }
        else {
            cur = p2;
        }
        if (cmd == "right") {
            cur->move("r");
            cout << *cur << endl;
        } else if (cmd == "left") {
            cur->move("l");
            cout << *cur << endl;
        } else if (cmd == "down") {
            cur->move("d");
            cout << *cur << endl;
        } else if (cmd == "drop") {
            cur->drop();
            if (player == true) {
                blockGen(*cur, l1.get(), true);
            }
            else {
                blockGen(*cur, l2.get(), true);
            }
            cout << *cur << endl;
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
                cout << *cur << endl;
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
                cout << *cur << endl;
            }
            catch (error) {}
        } else if (cmd == "I" || cmd == "L" || cmd == "J" || cmd == "O" ||
                   cmd == "S" || cmd == "Z" || cmd == "T") {
            bool done = cur->replaceCurr(cmd);
            cout << *cur << endl;
        } else if (cmd == "norandom file") {

        } else if (cmd == "random") {

        } else if (cmd == "sequence") {

        } else if (cmd == "restart") {

        } else if (cmd == "clockwise") {

        } else if (cmd == "counterclockwise") {

        }
        else {
            cout << "Invalid Argument!" << endl;
        }
    }
}