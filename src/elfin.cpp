#include <cstdio>
#include <cmath>
#include <vector>

#include "map.h"
#include "elfin.h"
#include "player.h"

//  class Elfin {
//    public:
//      int x, y;
//      int last_x, last_y;
//      int height, width;
//      int content[4][10];
//      char property;
//      int level; // 0 - MAP_H
//  }


void Elfin::init(int x0, int y0, int h, int w, int cont[][6], int proty, int lel) {
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


void elfin_move(Map& map, Player& player, bool& touch, bool& moving) {
  for (int i = 0; i < map.elfins.size(); i++) {
    if (map.elfins[i].level == player.x / BLOCK_H) {
      if (map.elfins[i].y == player.y && map.elfins[i].property % 10 != player.property) {
        touch = true;
        return;
      }
      int direc = 0;
      bool moving1 = false, moving2 = false;
      if (map.elfins[i].y != player.y) {
        direc = (map.elfins[i].y - player.y) / abs(map.elfins[i].y - player.y);
        moving1 = true;
      }
      else {
        direc = (map.elfins[i].last_y - map.elfins[i].y) / abs(map.elfins[i].last_y - map.elfins[i].y);
        moving1 = true;
      }
      //map.elfins[i].last_y = map.elfins[i].y;
      if (map.elfins[i].y - direc >= 0 && map.elfins[i].y - direc <= MAP_C) {
        map.elfins[i].last_y = map.elfins[i].y;
        map.elfins[i].y -= direc;
        moving2 = true;
      }
      if (moving1 && moving2)
        moving = true;
    }
  }
}





