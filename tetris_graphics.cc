#include "tetris_graphics.h"

void TetrisGraphics::display_block(Xwindow *w, vector<pair<int, int>> v, int player, char block_type) {
  int colour = 0;
  if (block_type == 'I') colour = 2; // red
  if (block_type == 'S') colour = 3; // blue
  if (block_type == 'L') colour = 6; // yellow
  if (block_type == 'Z') colour = 7; // green
  if (block_type == 'J') colour = 8; // magenta
  if (block_type == 'O') colour = 9; // orange
  if (block_type == 'T') colour = 10; // turquoise
    int x_origin = x0 + (player - 1) * s * board_width;

for (auto it = v.begin(); it !=v.end(); ++it) {
 int x = it->first;
 int y = it->second;
w->fillRectangle(x_origin + x * s, y0 + y * s, s, s, colour);
}
}
void TetrisGraphics::erase_block(Xwindow *w, vector<pair<int, int>> v, int player) {
    int x_origin = x0 + (player - 1) * s * board_width;
for (auto it = v.begin(); it !=v.end(); ++it) {
 int x = it->first;
 int y = it->second;
 if (player == 1) {
 w->fillRectangle(x_origin + x * s, y0 + y * s, s, s, Xwindow::Wheat);
 } else {
    w->fillRectangle(x_origin + x * s, y0 + y * s, s, s, Xwindow::Tan); 
 }
}
}

void TetrisGraphics::player1_init (Xwindow *w) {
  w->fillRectangle(x0, y0, s * board_width, s * board_height, Xwindow::Wheat);
  w->drawString(170, 90, "Player 1");
}

void TetrisGraphics::player2_init (Xwindow *w) {
  w->fillRectangle(x0 + s * board_width, y0, s * board_width, s * board_height, Xwindow::Tan);
  w->drawString(400, 90, "Player 2");
}
