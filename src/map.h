#ifndef HEADER_MAP
#define HEADER_MAP

#include "player.h"

#include <vector>

// size of block
#define BLOCK_H 5
#define BLOCK_W 10

// real size of map
#define MAP_R 60
#define MAP_C 160

//size of map in blocks
#define MAP_H 12
#define MAP_W 16

class Player;

class Block {
  public:
    void init(int);
    int x, y;
    int overall_property;
    int content[BLOCK_H][BLOCK_W];
};

class Map {
  public:
    void init(int);
    void print(void);
    void inspect(int);
    void check(Player&);
    void update(Player);
	Block get_portal(int, int, int);
    Block get_tar_portal(int, int, int);
    int content[MAP_R][MAP_C];
    int state;
    Block blocks[MAP_H][MAP_W];
};

#endif
