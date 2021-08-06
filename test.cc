#include <iomanip>
#include "board.h"
#include "RAIILevel.h"

using namespace std;

void blockGen(Board &b, generation *l, bool call) {
    char block = l->genBlock();
    string s(1, block);
    if (call) {
        b.next();
    }
    b.setNext(s);
}

ostream &operator<<(ostream &out, Board &b) {
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
    RAIILevel levelvector{"sequence1.txt"};
    shared_ptr<generation> l = levelvector.getLevel(3);
    b.setLevel(3);
    blockGen(b, l.get(), false);
    blockGen(b, l.get(), true);
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
            blockGen(b, l.get(), true);
            cout << b << endl;
        } else if (cmd == "level") {
            int level;
            cin >> level;
            try {
                l = levelvector.getLevel(level);
                b.setLevel(level);
                cout << b << endl;
            }
            catch (error) {
                cerr << "Error: Level not in bounds." << endl;
            }
        } else {
            cout << "Invalid Argument!" << endl;
        }
    }
}