#include "map.h"
#include "utils.h"
#include "player.h"
#include "unistd.h"

#include <cstdio>
#include <iostream>

int main() {
    
  Map map;
  map.init(60, 160); // blocks: 15x16
  map.print();

  Player player;
  player.init(1, 1, 2, 3, 0, 'i');

  Block portal;
  int temp0[4][10] = {10,10,10,10,10,0,0,0,0,0,10,10,10,10,10,0,0,0,0,0,10,10,10,10,10,0,0,0,0,0,10,10,10,10,10,0,0,0,0,0};
  char temp1[4][10] = {'p','p','p','p','p','x','x','x','x','x','p','p','p','p','p','x','x','x','x','x','p','p','p','p','p','x','x','x','x','x','p','p','p','p','p','x','x','x','x','x'};
  portal.init(0,3,temp0,temp1,10);
  map.blocks.push_back(portal);
  int temp2[4][10] = {0,0,0,0,0,11,11,11,11,11,0,0,0,0,0,11,11,11,11,11,0,0,0,0,0,11,11,11,11,11,0,0,0,0,0,11,11,11,11,11};
  char temp3[4][10] = {'x','x','x','x','x','p','p','p','p','p','x','x','x','x','x','p','p','p','p','p','x','x','x','x','x','p','p','p','p','p','x','x','x','x','x','p','p','p','p','p'};
  portal.init(0,12,temp2,temp3,11);
  map.blocks.push_back(portal);

  usleep(1000000); // the unit is miu_s

  map.update(player);
  std::cout << "\033[2J\033[1;1H";
  map.print();

  while (true) {
    
    map.check(player);

    char key = get_keyboard();
    std::cout<<key;
    if (key != 'x') {
      player.move(key, map);
    }

    map.check(player);
    map.update(player);
    std::cout << "\033[2J\033[1;1H";
    map.print();

    printf("x%d y%d xx%d yy%d\n", player.x, player.y, player.x % 4, player.y / 10);

  }

  return 0;

}
