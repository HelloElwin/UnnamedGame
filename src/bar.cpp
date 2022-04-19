#include <cstdio>
#include <cmath>
#include <vector>

#include "map.h"
#include "bar.h"
#include "player.h"

//  class Bar {
//    public:
//      int x, y;
//      int last_x, last_y;
//      int height, width;
//      int content[4][10];
//      char property;
//      int level; // 0 - MAP_H
//  }


void Bar::init(int x0, int y0, int h, int w, int cont[][6], int proty, int lel) {
  last_x = x = x0;
  last_y = y = y0;
  height = h;
  width = w;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      content[i][j] = cont[i][j];
    }
  }
  property = proty;
  level = lel;
}


void bar_move(Map& map, Player& player, bool& touch, bool& moving) {
  for (int i = 0; i < map.bars.size(); i++) {
    if (map.bars[i].level == player.x / BLOCK_H) {
      if (map.bars[i].y == player.y && map.bars[i].property % 10 != player.property) {
        touch = true;
        return;
      }
      int direc = 0;
      bool moving1 = false, moving2 = false;
      if (map.bars[i].y != player.y) {
        direc = (map.bars[i].y - player.y) / abs(map.bars[i].y - player.y);
        moving1 = true;
      }
      map.bars[i].last_y = map.bars[i].y;
      if (map.bars[i].y - direc >= 0 && map.bars[i].y - direc <= MAP_C) {
        map.bars[i].last_y = map.bars[i].y;
        map.bars[i].y -= direc;
        moving2 = true;
      }
      if (moving1 && moving2)
        moving = true;
    }
  }
}





