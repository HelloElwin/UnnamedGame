#include "map.h"
#include "utils.h"
#include "player.h"
#include "block_fill.h"

#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>

// class Block {
//   public:
//     void init(int);
//     int x, y;
//     int overall_property;
//     int content[BLOCK_H][BLOCK_W];
// };
// 
// class Map {
//   public:
//     void init(int);
//     void print(void);
//     void inspect(int);
//     void check(Player&);
//     void update(Player);
//     Block get_portal(int, int, int);
//     int content[MAP_R][MAP_C];
//     Block blocks[MAP_H][MAP_W];
//     int gravity; // verticle gravity only
// };

void Block::init(int property) {
  fill(property, (int*)content);
  overall_property = property;
}

void Map::inspect(int level) {
  if (level >= 1) {
    for (int i = 0; i < MAP_H; i++) {
      for (int j = 0; j < MAP_W; j++) {
        printf("%d  ", blocks[i][j].overall_property);
      }
      printf("\n");
    }
  }
  if (level >= 2) {
    for (int i = 0; i < MAP_R; i++) {
      for (int j = 0; j < MAP_C; j++) {
        printf("%d ", content[i][j]);
      }
      printf("\n");
    }
  }
}

void Map::init(int map_num) {

  for (int i = 0; i < MAP_R; i++)
    for (int j = 0; j < MAP_C; j++)
      content[i][j] = 0;

  std::string path = "lib/maps/" + std::to_string(map_num) + ".txt";
  std::ifstream map_file(path);

  for (int i = MAP_H - 1; i >= 0; i--) {
    for (int j = 0; j < MAP_W; j++) {
      int serial;
      char x;
      map_file >> x;
      if (x == '\n') map_file >> x;
      switch (x) {
        case '0':
          blocks[i][j].overall_property = 0;
          break;
        case '#':
          blocks[i][j].overall_property = 1;
          break;
        case '(': // up portal
          map_file >> serial >> x;
          blocks[i][j].overall_property = serial * 10 + 1;
          break;
        case ')': // down portal
          map_file >> serial >> x;
          blocks[i][j].overall_property = serial * 10 + 2;
          break;
        case '[': // left portal
          map_file >> serial >> x;
          blocks[i][j].overall_property = serial * 10 + 3;
          break;
        case ']': // right portal
          map_file >> serial >> x;
          blocks[i][j].overall_property = serial * 10 + 4;
          break;
        case '|': // gate
          blocks[i][j].overall_property = 4;
          break;
      }
    }
  }

  map_file.close();

  for (int i = 0; i < MAP_H; i++)
    for (int j = 0; j < MAP_W; j++) {
      blocks[i][j].x = i, blocks[i][j].y = j;
      blocks[i][j].init(blocks[i][j].overall_property);
    }

  gravity = 1;

}

void Map::print(void) {
  for (int i = MAP_R - 1; i >= 0; i--) {
    for (int j = 0; j < MAP_C; j++)
      super_print(content[i][j]);
    printf("\n");
  }
}

Block Map::get_portal(int tar, int player_xx, int player_yy) {
  Block ret;
  for (int i = 0; i < MAP_H; i++)
    for (int j = 0; j < MAP_W; j++) {
      if (player_xx == i && player_yy == j) continue;
      else if (blocks[i][j].overall_property / 10 == tar) ret = blocks[i][j];
    }
  return ret;
}

void Map::check(Player &u) {
  int x = u.x, y = u.y;
  for (int i = x; i < x + u.height; i++) 
    for (int j = y; j < y + u.width; j++) {
      if (content[i][j] % 100 >= 5) { // 贴进
        int xx = i / BLOCK_H, yy = j / BLOCK_W;
        Block portal = get_portal(content[i][j] % 100, xx, yy);
        if (portal.overall_property % 10 == 4) { // right 
          u.x = portal.x * BLOCK_H + 1;
          u.y = portal.y * BLOCK_W + 6;
        } 
        else if (portal.overall_property % 10 == 3){ // left
          u.x = portal.x * BLOCK_H + 1;
          u.y = portal.y * BLOCK_W - u.width;
        }
        return;
      }
    }
}

void Map::update(Player u) {

  for (int i = u.last_x; i < u.last_x + u.height; i++)
    for (int j = u.last_y; j < u.last_y + u.width; j++)
      content[i][j] = 0;

  for (int r = 0; r < MAP_H; r++)
    for (int c = 0; c < MAP_W; c++)
      for (int i = 0; i < BLOCK_H; i++)
        for (int j = 0; j < BLOCK_W; j++) {
          int x = r * BLOCK_H, y = c * BLOCK_W;
          int cont = blocks[r][c].content[BLOCK_H - i - 1][j];
          if (cont != 0) content[x + i][y + j] = cont;
        }

  for (int i = u.x; i < u.x + u.height; i++)
    for (int j = u.y; j < u.y + u.width; j++)
      content[i][j] = 3202; // 这要被换成！！角色像素的数字！！

}

