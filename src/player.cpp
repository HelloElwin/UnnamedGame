#include "player.h"
#include "utils.h"
#include "map.h"

//  class Player {
//    public:
//      void init(int, int, int, int, int, int[][10], int);
//      void move(char, Map&);
//      void check_floor(Map, bool*);
//      void inspect(int);
//      bool alive(Map&);
//      bool success(Map&);
//      int x, y;
//      int last_x, last_y;
//      int height, width;
//      int content[4][10];
//      int state; // 0-Outer 1-Inner
//      char property;
//      int speed; // verticle speed only
//      int real_speed; 
//      bool touching_gravity, last_touching_gravity;
//  };

void Player::init(int x0, int y0, int h0, int w0, int s0, int cont[][2], int proty) {
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
      if (i < 0 || i > MAP_R - height + 1) // over boundary
        return false;
      if ((map.content[i][j] % 100) / 10 == 3) // touch bar with opposite property
        if (property != (map.content[i][j] % 100) % 10)
          return false;
      if (map.blocks[xx][yy].overall_property / 10 == 2) // step onto ground with opposite property
        if (property != (map.blocks[xx][yy].overall_property % 10))
          return false;
    }
  }
  return true;
}

bool Player::success(Map& map) {
  for (int i = x; i < x + height; i++) {
    for (int j = y; j < y + width; j++) {
      if (map.content[i][j] % 100 == 4)
        return true;
    }
  }
  return false;
}

void Player::move(char direction, Map& map, bool& moving) {
  bool is_floor[4]; // up, down, left, right
  check_floor(map, is_floor);
  switch (direction) {
    case 'w':
      if (is_floor[0]) return;
      last_y = y;
      last_x = x++;
      moving = true;
      break;
    case 's':
      if (is_floor[1]) return;
      last_x = x--;
      last_y = y;
      moving = true;
      break;
    case 'a':
      if (is_floor[2]) return;
      last_x = x;
      last_y = y;
      y -= 2;
      moving = true;
      break;
    case 'd':
      if (is_floor[3]) return;
      last_x = x;
      last_y = y;
      y += 2;
      moving = true;
      break;
  }
  check_floor(map, is_floor);
  if (map.gravity < 0 && is_floor[1]) {
    speed = 0;
    real_speed = 0;
  }
  else if (map.gravity > 0 && is_floor[0]) {
    speed = 0;
    real_speed = 0;
  }
  else {
    speed += map.gravity;
    real_speed += map.gravity;
    last_x = x;
    int bound = speed > 0 ? x + height : x;
    int addpos = 0;
    bool special0 = false;
    if (abs(speed) > 0) {
      addpos = speed / abs(speed);
      for (int j = 0; j < width; j++) {
        if (map.content[bound + addpos][y + j] % 100 != 0) {
          special0 = true;
          real_speed -= map.gravity;
          break;
        }
      }
    }
    if (!special0)
      speed = real_speed;
    if (abs(speed) > 1) {
      bool special = false;
      for (int j = 0; j < width; j++) {
        int pos = addpos;
        while (pos != speed + addpos) {
          if (bound + pos <= MAP_R && bound + pos >= 0 && map.content[bound + pos][y + j] % 100 != 0) {
            special = true;
            speed = pos - addpos;
            break;
          }
          pos += addpos;
        }
        if (special)
          break;
      }
    }
    x += speed;
    moving = true;
  }
}

void Player::check_floor(Map map, bool* is_floor) {
  // initialize
  for (int i = 0; i < 4; i++) is_floor[i] = false;
  // up
  //if (x + 1 >= MAP_R) is_floor[0] = true;
  for (int i = 0; i < width; i++)
    if (map.content[x + height][y + i] % 100 == 1 || (map.content[x + height][y + i] % 100) / 10 == 2) is_floor[0] = true;
  // down
  //if (x - 1 < 0) is_floor[1] = true;
  for (int i = 0; i < width; i++)
    if (map.content[x - 1][y + i] % 100 == 1 || (map.content[x - 1][y + i] % 100) / 10 == 2) is_floor[1] = true;
  // left
  if (y - 2 < 0) is_floor[2] = true;
  if (map.content[x][y - 1] % 100 == 1 || map.content[x][y - 2] % 100 == 1) is_floor[2] = true;
  // right
  if (y + width + 1 >= MAP_C) is_floor[3] = true;
  for (int i = 0; i < height; i++)
    if (map.content[x + i][y + width + 2] % 100 == 1 || map.content[x + i][y + 1] % 100 == 1) is_floor[3] = true;
}
