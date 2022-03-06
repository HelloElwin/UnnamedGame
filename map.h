#ifndef MAP_H
#define MAP_H

#include "player.h"

class Player;

class Map {
  public:
    void init(int, int);
    void print(void);
    void update(Player);
    int content[200][200];
    int row;
    int col;
    int state; // 0 for Outer World and 1 for Inner World
};

#endif
