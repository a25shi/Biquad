#ifndef _BLOCK_H
#define _BLOCK_H

#include <iostream>
#include <vector>

using namespace std;

class Block {
    int genLevel;
    string type;
    bool temp;
    vector<vector<int>> coord;
    vector<vector<int>> rotation;
    int stage;
    
    public:
        Block();
        Block(int level, vector<vector<int>> coord);
        Block(string type, vector<vector<int>> coord, int level, int stage);
        ~Block();
        string getType() const;
        bool isTemp() const;
        void setTemp(bool state);
        vector<vector<int>> getCoord() const;
        vector<vector<int>> changeCoord(int diff, string axis) const;
        void removeCoord(int x, int y);
        int getActiveCoord() const;
        int getLevel() const;
        int getStage() const;
        void setStage(int setTo);
        vector<vector<int>> rotatedCoords(string dir);
};


#endif //BIQUAD_BLOCK_H
