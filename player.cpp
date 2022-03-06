#include "player.h"
#include "utils.h"
#include "map.h"

// class Player {
//   public:
//     void init(int, int, int);
//     void move(void);
//     int x, y;
//     int last_x, last_y;
//     int height, width;
//     int state; // 0-Outer 1-Inner
// };

void Player::init(int x0, int y0, int h0, int w0, int s0) {
  x = last_x = x0;
  y = last_y = y0;
  height = h0;
  width = w0;
  state = s0;
}

void Player::move(char direction, Map& map) {
  switch (direction) {
    case 'u':
      // Cannot move upwards
      break;
    case 's':
      if (x - 1 < 0 || map.content[x - 1][y] == 1) break;
      last_x = x--;
      break;
    case 'a':
      if (y - 1 < 0 || map.content[x][y - 1] == 1) break;
      last_y = y--;
      break;
    case 'd':
      if (y - 1 >= map.col || map.content[x][y + 1] == 1) break;
      last_y = y++;
      break;
  }
}
