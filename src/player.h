#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"

class Map;

class Player {
  public:
    void init(int, int, int, int, int, int[][2], int);
    void move(char, Map&, bool&);
    void check_floor(Map, bool*);
    void inspect(int);
	bool alive(Map&);
	bool success(Map&);
    int x, y;
    int last_x, last_y;
    int height, width;
    int content[4][10];
    int state; // 0-Outer 1-Inner
    char property;
    int speed; // verticle speed only
	int real_speed;
    bool touching_gravity, last_touching_gravity;
};

#endif
