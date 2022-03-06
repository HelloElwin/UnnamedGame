#include "map.h"
#include "utils.h"
#include "player.h"
#include "unistd.h"
#include "blocks.h"

#include <cstdio>
#include <iostream>

int main() {
    
  Map map;
  map.init(60, 160); // 之后要改为从地图初始化
  map.print();

  Player player;
  player.init(1, 1, 2, 1, 0, 'i');

  Block portal;
  int temp0[4][10] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5};
  char temp1[4][10] = {'x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p','p'};
  portal.init(2,30,temp0,temp1,5);
  map.blocks.push_back(portal);

  usleep(1000000); // the unit is miu_s

  map.update(player);
  std::cout << "\033[2J\033[1;1H";
  map.print();

  while (true) {
    
    char key = get_keyboard();
    std::cout<<key;
    if (key != 'x') {
      player.move(key, map);
    }

    // check();
    map.update(player);
    std::cout << "\033[2J\033[1;1H";
    map.print();

  }

  return 0;

}
