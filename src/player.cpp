#include "player.h"
#include "utils.h"
#include "map.h"

// class Player {
//   public:
//     void init(int, int, int, int, int, int[][10]);
//     void move(char, Map&);
//     void inspect(void);
//     int x, y;
//     int last_x, last_y;
//     int height, width;
// 	   int content[4][10];
//     int state; // 0-Outer 1-Inner
//     char property;
// };

void Player::init(int x0, int y0, int h0, int w0, int s0, int cont[][10]) {
  x = last_x = x0;
  y = last_y = y0;
  height = h0;
  width = w0;
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      content[i][j] = cont[i][j]; // !! content of the player
    }
  }
  state = s0;
}

void Player::inspect(int level) {
  if (level >= 1) {
    printf("Player Info: x%d y%d xx%d yy%d last_x%d last_y%d state%d\n", x, y, x / 5, y / 10, last_x, last_y, state);
  }
  if (level >= 2) {
    printf("Player Content:\n");
    for (int i = 0; i < height; i++) {
      printf("  ");
      for (int j = 0; j < width; j++) {
        printf("%d ", content[i][j]);
      }
      printf("\n");
    }
  }
}

void Player::move(char direction, Map& map) {
  switch (direction) {
    case 'w':
      // Cannot move upwards
      if (x + height + 1 >= MAP_R) return;
      for (int i = 0; i < width; i++)
        if (map.content[x + 1][y + i] % 100 == 1) return;
      last_y = y;
      last_x = x++;
      break;
    case 's':
      if (x - 1 < 0) return;
      for (int i = 0; i < width; i++)
        if (map.content[x - 1][y + i] % 10 == 1) return;
      last_y = y;
      last_x = x--;
      break;
    case 'a':
      if (y - 2 < 0 || map.content[x][y - 1] % 100 == 1 || map.content[x][y - 2] % 100 == 1) return;
      last_y = y;
      last_x = x;
      y -= 2;
      break;
    case 'd':
      if (y + width + 1 >= MAP_C) return;
      for (int i = 0; i < height; i++)
        if (map.content[x + i][y] % 100 == 1 || map.content[x + i][y + 1] % 100 == 1) return;
      last_x = x;
      last_y = y;
      y += 2;
      break;
  }
}
