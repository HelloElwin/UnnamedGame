#include <vector>

#ifndef HEADER_MAP
#define HEADER_MAP

#include "player.h"
#include "elfin.h"

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
    void init(int, int[]);
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
    void converter(Player&);
    Block get_tar_portal(int, int, int, bool&);
    int content[MAP_R][MAP_C];
    int portal_color[8];
    Block blocks[MAP_H][MAP_W];
    int gravity; // verticle gravity only
    std::vector<Elfin> elfins;
};

#endif
