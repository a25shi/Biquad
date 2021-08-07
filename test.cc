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
    out << endl;
    out << "Level:";
    out << right;
    out << setw(5) << b.getLevel() << endl;

    out << "Score:";
    out << right;
    out << setw(5) << b.getScore() << endl;

    out << string(11, '-') << endl;
    bool isBlind = b.getBlind();
    for (int y = 17; y >= 0; y--) {
        for (int x = 0; x < 11; x++) {
            if (isBlind) {
                if (x >= 2 && x <= 8 &&
                    y >= 2 && y <= 12) {
                        out << "?";
                    }
                else {
                    out << b.getVal(x, y);
                }
            } else {
                out << b.getVal(x, y);
            }
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
        if (cmd == "right") {
            b.move("r");
            if (b.getHeavy()) {
                bool move1 = b.move("d");
                bool move2 = b.move("d");
                if (!(move1 && move2)) {
                    b.drop();
                    b.setHeavy(false);
                }
            }
            cout << b << endl;
        } else if (cmd == "left") {
            b.move("l");
            if (b.getHeavy()) {
                bool move1 = b.move("d");
                bool move2 = b.move("d");
                if (!(move1 && move2)) {
                    b.drop();
                    b.setHeavy(false);
                }
            }
            cout << b << endl;
        } else if (cmd == "down") {
            b.move("d");
            cout << b << endl;
        } else if (cmd == "drop") {
            b.drop();
            if (b.getBlind()) {
                b.setBlind(false);
            }
            if (b.getHeavy()) {
                b.setHeavy(false);
            }
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
        } else if (cmd == "force") {
            string shape;
            cin >> shape;
            if (!(shape == "I" || shape == "L" || shape == "J" || shape == "O" ||
                  shape == "S" || shape == "Z" || shape == "T")) {
                    cout << "invalid block type" << endl;
            } else {
                bool done = b.replaceCurr(shape);
            }
            
            cout << b << endl;
        } else if (cmd == "counter") {
            bool done = b.rotate("cc");
            cout << b << endl;
        } else if (cmd == "clockwise") {
            bool done = b.rotate("c");
            cout << b << endl;
        } else if (cmd == "blind") {
            b.setBlind(true);
            cout << b << endl;
        } else if (cmd == "heavy") {
            b.setHeavy(true);
            cout << b << endl;
        } else {
            cout << "Invalid Argument!" << endl;
        }
    }
}