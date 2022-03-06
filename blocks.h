#ifndef BLOCKS_H
#define BLOCKS_H

#include "map.h"

class Map;

class Block {
  public:
    void init(int, int, int[][10], char[][10], int);
    void move(char, Map&);
    int x, y;
    int last_x, last_y;
    int overall_property;
    int content[4][10];
    char property[4][10];
};

#endif
