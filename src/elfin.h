#include "map.h"
#include "player.h"

#ifndef ELFIN_YEAH
#define ELFIN_YEAH

#define ELFIN_H 4
#define ELFIN_W 6

class Elfin {
  public:
    int x, y;
    int last_x, last_y;
    int height, width;
    int content[ELFIN_H][ELFIN_W];
    char property;
    void init(int, int, int, int, int cont[][ELFIN_W], int, int);
    int level; // 0 - MAP_H
};

class Map;
class Player;

void elfin_move(Map&, Player&, bool&, bool&);

#endif
