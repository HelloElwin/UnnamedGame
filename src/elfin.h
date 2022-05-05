#include "map.h"
#include "player.h"

#ifndef ELFIN_H
#define ELFIN_H


class Elfin {
  public:
    int x, y;
    int last_x, last_y;
    int height, width;
    int content[4][6];
    char property;
    void init(int, int, int, int, int cont[][6], int, int);
    int level; // 0 - MAP_H
};

class Map;
class Player;

void elfin_move(Map&, Player&, bool&, bool&);

#endif
