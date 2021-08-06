#include "board.h"
using namespace std;

ostream& operator<<( ostream & out, Board &b) {
    cout << string(21, '-') << endl;
    for (int y = 17; y >= 0; y--) {
        for (int x = 0; x < 11; x++) {
            if (x != 0) {
                out << " ";
            }
            //cout << "here?" << endl;
            out << b.getVal(x, y);
        }
        out << endl;
    }

    return out;
}

int main(int args, char *argv[]) {
    Board b;
    cout << b << endl;
    b.next("I");
    cout << b << endl;
    char cmd;
    while (cin >> cmd) {
        switch (cmd) {
            case 'r': {
                b.move("r");
                cout << b << endl;
                break;
            }
            case 'l': {
                b.move("l");
                cout << b << endl;
                break;
            }
            case 'd': {
                b.move("d");
                cout << b << endl;
                break;
            }
        }
    }
}