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
const int bwid = 5; //row of a block
const int blen = 10; // column of a block

//void Block::init(int x0, int y0, int cont[][blen], char prop[][blen], int p0) {
void Block::init(int x0, int y0, int cont[][blen], int p0) {
  x = last_x = x0;
  y = last_y = y0;
  for (int i = 0; i < bwid; i++) {
    for (int j = 0; j < blen; j++) {
      content[i][j] = cont[i][j];
      //property[i][j] = prop[i][j];
    }
  }
  overall_property = p0;
}

int get_portal(int tar, std::vector<Block> blocks, int player_xx, int player_yy) {
  for (int i = 0; i < blocks.size(); i++) {
    //if (blocks[i].overall_property / 10 == tar / 10 && blocks[i].overall_property % 10 != tar % 10) {
    if (blocks[i].overall_property / 10 == tar  && (player_xx != blocks[i].x || player_yy != blocks[i].y)) {
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
//    super_print(content[i][j], property[i][j]); // 在utils里，输出特定“像素”
      super_print(content[i][j]);
    }
    printf("\n");
  }
}

void Map::check(Player &u) {
  int x = u.x, y = u.y;
  int polwid = 2;
  for (int i = x; i < x + u.height; i++) 
    for (int j = y; j < y + u.width; j++)
      if (content[i][j] % 100 >= 10) { // 贴进
        int xx = i / bwid, yy = j / blen;
        int id = get_portal(content[i][j] % 100, blocks, xx, yy);
        Block portal = blocks[id];
        if (portal.overall_property % 10 == 4) { //right 
          u.x = portal.x * bwid + 1;
          u.y = portal.y * blen + 6;
        } 
        else if (portal.overall_property % 10 == 3){ //left
          u.x = portal.x * bwid + 1;
          u.y = portal.y * blen - u.width + 3;
        }
        return;
      }
}

void Map::update(Player u) {
  for (int i = u.last_x; i < u.last_x + u.height; i++)
    for (int j = u.last_y; j < u.last_y + u.width; j++) {
      content[i][j] = 0;
    //property[i][j] = 'x';
    }
  int ii = u.height - 1,jj = 0;
  for (int i = u.x; i < u.x + u.height; i++, ii--) {
    jj = 0;
    for (int j = u.y; j < u.y + u.width; j++, jj++) {
      content[i][j] = 3202; // 这要被换成！！角色像素的数字！！
    //property[i][j] = u.property;
    }
  }
  for (int idx = 0; idx < blocks.size(); idx++)
    for (int i = 0; i < bwid; i++) {
      for (int j = 0; j < blen; j++) {
        int xx = blocks[idx].x, yy = blocks[idx].y;
        int x = xx * bwid, y = yy * blen;
        if(blocks[idx].content[i][j]!=0) {
          content[x + i][y + j] = blocks[idx].content[i][j];
       // property[x + i][y + j] = blocks[idx].property[i][j];
        }
      }
  }
}

