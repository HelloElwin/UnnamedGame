#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"

class Map;

class Player {
  public:
    void init(int, int, int, int, int, char);
    void move(char, Map&);
    int x, y;
    int last_x, last_y;
    int height, width;
    int state; // 0-Outer 1-Inner
    char property;
};

#endif
