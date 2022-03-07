#ifndef MAP_H
#define MAP_H

#include "player.h"

#include <vector>

class Player;

class Block {
  public:
    void init(int, int, int[][10], char[][10], int);
    // void move(char);
    int x, y;
    int last_x, last_y;
    int overall_property;
    int content[4][10];
    char property[4][10];
};

class Map {
  public:
    void init(int, int);
    void print(void);
    void check(Player&);
    void update(Player);
    int content[200][200];
    char property[200][200];
    int row;
    int col;
    int state; // 0-Outer 1-Inner
    std::vector<Block> blocks;
};

int get_portal(int, std::vector<Block>, int, int);

#endif
