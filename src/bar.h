#ifndef BAR_H
#define BAR_H

#include "map.h"
#include "player.h"

class Bar {
	public:
		int x, y;
		int last_x, last_y;
		int height, width;
		int content[4][10];
		char property;
		int level; // 0 - MAP_H
}

class Map;
class Player;

#endif
