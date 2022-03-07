#include "map.h"
#include "utils.h"
#include "player.h"

#include <cstdio>
#include <iostream>

// class Map {
//   public:
//     void init(int, int);
//     void print(void);
//     void check(Player);
//     void update(Player);
//     int content[200][200];
//     char property[200][200];
//     int row;
//     int col;
//     int state; // 0-Outer 1-Inner
//     std::vector<Block> blocks;
// };
//
const int Row = 4;
const int Column = 10;
//void Block::init(int x0, int y0, int cont[][Column], char prop[][Column], int p0) {
void Block::init(int x0, int y0, int cont[][Column], int p0) {
  x = last_x = x0;
  y = last_y = y0;
  for (int i = 0; i < Row; i++) {
    for (int j = 0; j < Column; j++) {
      content[i][j] = cont[i][j];
      //property[i][j] = prop[i][j];
    }
  }
  overall_property = p0;
}

int get_portal(int tar, std::vector<Block> blocks) {
  for (int i = 0; i < blocks.size(); i++) {
    if (blocks[i].overall_property / Column == tar / Column && blocks[i].overall_property % Column != tar % Column) {
      return i;
    }
  }
  return -1;
}


void Map::init(int r, int c) {
  row = r;
  col = c;
  state = 0;
  for (int i = 0; i < r; i++)
    for (int j = 0; j < c; j++) {
      content[i][j] = ((i == 0 || i == r - 1) ? 23101 : 0);
      //property[i][j] = 'x';
    }
}

void Map::print(void) {
  for (int i = row - 1; i >= 0; i--) {
    for (int j = 0; j < col; j++) {
//      super_print(content[i][j], property[i][j]); // 在utils里，输出特定“像素”
		super_print(content[i][j]);
    }
    printf("\n");
  }
}

void Map::check(Player &u) {
  int x = u.x, y = u.y;
  for (int i = x; i < x + u.height; i++) 
    for (int j = y; j < y + u.width; j++)
      if (content[i][j] % 100 >= 10) { // 贴进
        int xx = i / Row, yy = j / Column;
        int id = get_portal(content[i][j] % 100, blocks);
        Block portal = blocks[id];
        if (portal.overall_property % 10 == 1) {
          u.x = portal.x * Row + 1;
          u.y = portal.y * Column + 10;
        } else if (portal.overall_property % 10 == 0){
          u.x = portal.x * Row + 1;
          u.y = portal.y * Column - u.width;
        }
        return;
      }
}

void Map::update(Player u) {
  for (int i = u.last_x; i < u.last_x + u.height; i++)
    for (int j = u.last_y; j < u.last_y + u.width; j++) {
      content[i][j] = 0;
    //  property[i][j] = 'x';
    }
  for (int i = u.x; i < u.x + u.height; i++)
    for (int j = u.y; j < u.y + u.width; j++) {
      content[i][j] = 2; // 这要被换成！！角色像素的数字！！
     // property[i][j] = u.property;
    }
  for (int idx = 0; idx < blocks.size(); idx++)
    for (int i = 0; i < Row; i++)
      for (int j = 0; j < Column; j++) {
        int xx = blocks[idx].x, yy = blocks[idx].y;
        int x = xx * Row, y = yy * Column;
        content[x + i][y + j] = blocks[idx].content[i][j];
       // property[x + i][y + j] = blocks[idx].property[i][j];
      }
}

