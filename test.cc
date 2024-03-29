#include "controller.h"
#include <iostream>
#include <sstream>
using namespace std;

const int ASK = 1;
const int START_NEW = 0;
const int QUIT = -1;

int main(int argc, char *argv[]) {
    bool graphic = true;
    int count = 1;
    int level = 0;
    string in1 = "sequence1.txt";
    string in2 = "sequence2.txt";
    while (count < argc) {
        string command = argv[count];
        if (command == "-text") {
            graphic = false;
        }
        if (command == "-seed") {
            unsigned int seeds;
            ++count;
            string num = argv[count];
            istringstream iss{num};
            iss >> seeds;
            srand(seeds);
        }
        if (command == "-scriptfile1") {
            ++count;
            string file = argv[count];
            in1 = file;
        }
        if (command == "-scriptfile2") {
            ++count;
            string file = argv[count];
            in2 = file;
        }
        if (command == "-startlevel") {
            ++count;
            string numLev = argv[count];
            istringstream iss{numLev};
            iss >> level;
        }
        ++count;
    }
    
    char cmd;
    bool continueGame = true;
    int gameNo = 1;
    while (true) {
        int restartGame = START_NEW;
        if (continueGame || (restartGame == START_NEW)) {
            Board p1;
            Board p2;
            p1.setLevel(level);
            p2.setLevel(level);
            Controller ct{&p1, &p2};
            restartGame = ct.play(in1, in2, level, gameNo, graphic);
        }

        if (restartGame == ASK) {
            cout << "\nWould you like to play again? (Y / N)" << endl;
            cin >> cmd;
            if (cmd == 'N') {
                continueGame = false;
                break;
            } else if (cmd == 'Y') {
                continueGame = true;
                gameNo++;
            } else {
                continueGame = false;
                cout << "Invalid command, try again!" << endl;
            }
        } 
    
        if (restartGame == QUIT) {
            break;
        }
    }
}

