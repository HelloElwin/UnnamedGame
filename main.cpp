#include "map.h"
#include "utils.h"
#include "player.h"
#include "unistd.h"
#include "block_fill.h"

#include <cstdio>
#include <iostream>

int main() {
    
  Map map;
  map.init(60, 160); // blocks: 15x16
  map.print();

  Player player;
  int cont0[4][10];
  //fill(21, (int*)cont0);
  player.init(1, 1, 2, 1, 0,cont0);

  Block portal;
  int cont1[5][10];
  fill(113, (int*)cont1);
  portal.init(0,3, cont1, 113);
  map.blocks.push_back(portal);

  Block portal2;
  int cont2[5][10];
  fill(114, (int*)cont2);
  portal2.init(0, 12, cont2, 114);
  map.blocks.push_back(portal2);

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

    printf("x%d y%d xx%d yy%d\n", player.x, player.y, player.x / 5, player.y / 10);
  }

  return 0;

}
