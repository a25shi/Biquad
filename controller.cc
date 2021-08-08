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
        for (int x = 0; x < 11; x++) {
            out << boards[0]->getVal(x, y);
        }
        out << setw(5)  << " ";
        for (int i = 0; i < 11; i++) {
            out << boards[1]->getVal(i, y);
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

void controller::play(string text1, string text2, int init) {
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
    while (cin >> cmd) {
        if (player == true) {
            cur = p1;
        }
        else {
            cur = p2;
        }
        if (cmd == "right") {
            cur->move("r");
            if (cur->getHeavy()) {
                bool move1 = cur->move("d");
                bool move2 = cur->move("d");
                if (!(move1 && move2)) {
                    cur->drop();
                    cur->setHeavy(false);
                }
            }
            cout << boards << endl;
        } else if (cmd == "left") {
            if (cur->getHeavy()) {
                bool move1 = cur->move("d");
                bool move2 = cur->move("d");
                if (!(move1 && move2)) {
                    cur->drop();
                    cur->setHeavy(false);
                }
            }
            cur->move("l");
            cout << boards << endl;
        } else if (cmd == "down") {
            cur->move("d");
            cout << boards << endl;
        } else if (cmd == "drop") {
            cur->drop();
            if (cur->getBlind()) {
                cur->setBlind(false);
            }
            if (cur->getHeavy()) {
                if (cur->getLevel() != 3 || cur->getLevel() != 4) {
                    cur->setHeavy(false);
                }
            }
            if (player == true) {
                blockGen(*cur, l1.get(), true);
            }
            else {
                blockGen(*cur, l2.get(), true);
            }
            cout << boards << endl;
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
            bool done = cur->replaceCurr(cmd);
            cout << boards << endl;
        } else if (cmd == "norandom") {

        } else if (cmd == "random") {

        } else if (cmd == "sequence") {

        } else if (cmd == "restart") {

        } else if (cmd == "clockwise") {
            bool done = cur->rotate("c");
            cout << boards << endl;
        } else if (cmd == "counterclockwise") {
            bool done = cur->rotate("cc");
            cout << boards << endl;
        }
        else {
            cout << "Invalid Argument!" << endl;
        }
    }
}