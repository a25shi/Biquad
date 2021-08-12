#ifndef __TETRIS_GRAPHICS_H__
#define __TETRIS_GRAPHICS_H__

#include <utility>
#include <vector>
#include "window.h"

using namespace std;

struct TetrisGraphics {
    int s = 20; // num of pixels per unit
    int board_width = 11;
    int board_height = 18;
    int x0 = 100;
    int y0 = 100;
    int onedrop = 800000;
    
    public:
      void display_block (Xwindow *w, vector<vector<int>> v, int player, string block_type);
      void erase_block (Xwindow *w, vector<vector<int>> v, int player);
      void player1_init (Xwindow *w);
      void player2_init (Xwindow *w);
  
};

#endif