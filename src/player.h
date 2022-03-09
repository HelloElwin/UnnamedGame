#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"

class Map;

class Player {
  public:
    void init(int, int, int, int, int, int[][10]);
    void move(char, Map&);
    void inspect(int);
    int x, y;
    int last_x, last_y;
    int height, width;
    int content[4][10];
    int state; // 0-Outer 1-Inner
    char property;
};

#endif
