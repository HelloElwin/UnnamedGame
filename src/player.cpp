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

void Player::init(int x0, int y0, int h0, int w0, int s0, int cont[][10], int proty) {
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
  property = proty;
  last_touching_gravity = 0;
}

void Player::inspect(int level) {
  if (level >= 1) {
    printf("Player Info: x%d y%d xx%d yy%d last_x%d last_y%d state%d touching_gravity%d last_touching_gravity%d\n", x, y, x / 5, y / 10, last_x, last_y, state, touching_gravity, last_touching_gravity);
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

bool Player::alive(Map& map) {
  for (int i = x; i < x + height; i++) {
    for (int j = y; j < y + width; j++) {
      int xx = i / BLOCK_H, yy = j / BLOCK_W;
      if (i < 0 || i > MAP_R - height + 1)
        return false;
      if ((map.content[i][j] % 100) / 10 == 3)
        if (property != (map.content[i][j] % 100) % 10)
          return false;
      if (map.blocks[xx][yy].overall_property / 10 == 1)
        if (property != (map.blocks[xx][yy].overall_property % 10))
          return false;
    }
  }
  return true;
}

void Player::move(char direction, Map& map) {
  bool is_floor[4]; // up, down, left, right
  check_floor(map, is_floor);
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
      if (is_floor[1]) return;
      last_x = x--;
      last_y = y;
      break;
    case 'a':
      if (is_floor[2]) return;
      last_x = x;
      last_y = y;
      y -= 2;
      break;
    case 'd':
      if (is_floor[3]) return;
      last_x = x;
      last_y = y;
      y += 2;
      break;
  }
  check_floor(map, is_floor);
  if (map.gravity < 0 && is_floor[1]) speed = 0;
  else if (map.gravity > 0 && is_floor[0]) speed = 0;
  else {
    speed = map.gravity;
    last_x = x;
    x += speed;
  }
}

void Player::check_floor(Map map, bool* is_floor) {
  // initialize
  for (int i = 0; i < 4; i++) is_floor[i] = false;
  // up
  if (x + 1 >= MAP_R) is_floor[0] = true;
  for (int i = 0; i < width; i++)
    if (map.content[x + height][y + i] % 100 == 1) is_floor[0] = true;
  // down
  if (x - 1 < 0) is_floor[0] = true;
  for (int i = 0; i < width; i++)
    if (map.content[x - 1][y + i] % 100 == 1) is_floor[1] = true;
  // left
  if (y - 2 < 0) is_floor[2] = true;
  if (map.content[x][y - 1] % 100 == 1 || map.content[x][y - 2] % 100 == 1) is_floor[2] = true;
  // right
  if (y + width + 1 >= MAP_C) is_floor[3] = true;
  for (int i = 0; i < height; i++)
    if (map.content[x + i][y + width + 2] % 100 == 1 || map.content[x + i][y + 1] % 100 == 1) is_floor[3] = true;
}
