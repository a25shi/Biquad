#include <iomanip>
#include "board.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
using namespace std;

void blockGen(Board &b, generation* l, bool call) {
    char block = l->genBlock();
    string s (1, block);
    if (call) {
        b.next();
    }
    b.setNext(s);
}

ostream& operator<<( ostream & out, Board &b) {
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
    out << "Type is: " << b.getNext() << endl;

    return out;
}

int main(int argc, char *argv[]) {
    Board b;
    level1 l;
    blockGen(b, &l, false);
    blockGen(b, &l, true);
    cout << b << endl;
    string cmd;
    while (cin >> cmd) {
        if (cmd == "move") {
            char dir;
            cin >> dir;
            if (dir == 'r') {
                b.move("r");
                cout << b << endl;
            } else if (dir == 'l') {
                b.move("l");
                cout << b << endl;
            } else if (dir == 'd') {
                b.move("d");
                cout << b << endl;
            } else {
                cout << "Invalid Direction!" << endl;
            }
        } else if (cmd == "drop") {
            b.drop();
            blockGen(b, &l, true);
            cout << b << endl;
        } else {
            cout << "Invalid Argument!" << endl;
        }
    }
}