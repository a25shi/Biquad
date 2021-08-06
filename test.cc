#include "board.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
using namespace std;

void blockGen(Board &b, generation* l) {
    char block = l->genBlock();
    string s (1, block);
    b.next(s);
}

ostream& operator<<( ostream & out, Board &b) {
    cout << string(21, '-') << endl;
    for (int y = 17; y >= 0; y--) {
        for (int x = 0; x < 11; x++) {
            if (x != 0) {
                out << " ";
            }
            out << b.getVal(x, y);
        }
        out << endl;
    }

    return out;
}

int main(int argc, char *argv[]) {
    Board b;
    level1 l;
    cout << b << endl;
    blockGen(b, &l);
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
            blockGen(b, &l);
            cout << b << endl;
        } else {
            cout << "Invalid Argument!" << endl;
        }
    }
}