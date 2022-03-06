#ifndef MAP_H
#define MAP_H

#include "player.h"
#include "blocks.h"

#include <vector>

class Player;
class Block;

class Map {
  public:
    void init(int, int);
    void print(void);
    void update(Player);
    int content[200][200];
    char property[200][200];
    int row;
    int col;
    int state; // 0-Outer 1-Inner
    std::vector<Block> blocks;
};

#endif
