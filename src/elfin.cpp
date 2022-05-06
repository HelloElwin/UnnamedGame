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
//      int content[4][6];
//      char property;
//      int level; // 0 - MAP_H
//  }


/*
   initialize the elfin
    · attach coordinates and its size
    · fill the content
    · attach the stata, property and the level it's on
   input:
    · int variables x0, y0, h0, w0, the coordinates, height and width
    · int cont[4][6]
    · int variables proty, lel, the property and the level
   no return value
*/
void Elfin::init(int x0, int y0, int h, int w, int cont[][ELFIN_W], int proty, int lel) {
  last_x = x = x0;
  last_y = y = y0;
  height = h;
  width = w;
  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
      content[i][j] = cont[i][j];
  property = proty;
  level = lel;
}


/*
   move the elfin according to player's position
   input:
    · an object of class Map
    · an object of class Player
    · a bool variable indicating whether the player touches elfins
    · a bool variable indicating whether there's any elfin moving
   return value:
    · bool variable touch, true if the player touches elfins, false if not
    · bool variable moving, true if any elfin moves, false if not
*/
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
