#include "board.h"
using namespace std;

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
    cout << b << endl;
    if (argc == 2) {
        string newBlock = string(1, argv[1][0]);
        b.next(newBlock);
    } else {
        b.next("L");
    }
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
            cout << b << endl;
        } else {
            cout << "Invalid Argument!" << endl;
        }
    }
}