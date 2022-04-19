#include "map.h"
#include "player.h"

#ifndef BAR_H
#define BAR_H


class Bar {
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

void bar_move(Map&, Player&, bool&, bool&);

#endif
