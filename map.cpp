#include "map.h"
#include "utils.h"
#include "player.h"

#include <cstdio>
#include <iostream>

// class Map {
//   public:
//     void init(int, int);
//     void print(void);
//     void update(player);
//     map content[200][200];
//     int row;
//     int col;
//     int state;
// };

void Map::init(int r, int c) {
  row = r;
  col = c;
  state = 0;
  for (int i = 0; i < r; i++)
    for (int j = 0; j < c; j++) {
      content[i][j] = ((i == 0 || i == r - 1) ? 1 : 0);
      property[i][j] = 'x';
    }
}

void Map::print(void) {
  for (int i = row - 1; i >= 0; i--) {
    for (int j = 0; j < col; j++) {
      super_print(content[i][j], property[i][j]); // 在utils里，输出特定“像素”
    }
    printf("\n");
  }
}

void Map::update(Player u) {
  for (int i = u.last_x; i < u.last_x + u.height; i++)
    for (int j = u.last_y; j < u.last_y + u.width; j++)
      content[i][j] = 0;
  for (int i = u.x; i < u.x + u.height; i++)
    for (int j = u.y; j < u.y + u.width; j++)
      content[i][j] = 1; // 这要被换成！！角色像素的数字！！
}
