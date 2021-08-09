#include "controller.h"
#include <iostream>
#include <sstream>
#include "tetris_graphics.h"
#include "window.h"
using namespace std;

int main(int argc, char *argv[]) {
    Xwindow w;
    TetrisGraphics tg;
 // the following are dummy coordinates for testing purposes
  pair <int, int> p1 = {2, 3};
  pair <int, int> p2 = {3, 3};
  pair <int, int> p3 = {4, 3};
  pair <int, int> p4 = {5, 3};
  vector <pair<int, int>> v;
  v.push_back(p1);
  v.push_back(p2);
  v.push_back(p3);
  v.push_back(p4);
  // the board initializes here 
  tg.player1_init(&w);
  tg.player2_init(&w);
  tg.display_block(&w, v, 1, 'S');
  tg.display_block(&w, v, 2, 'O');
  //tg.erase_block(&w, v, 1);
  //tg.erase_block(&w, v, 2);

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
        if (continueGame) {
            Board p1;
            Board p2;
            p1.setLevel(level);
            p2.setLevel(level);
            Controller ct{&p1, &p2};
            ct.play(in1, in2, level, gameNo);
        }

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
}

