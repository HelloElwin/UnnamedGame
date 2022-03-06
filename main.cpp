#include "map.h"
#include "utils.h"
#include "player.h"
#include "unistd.h"

#include <cstdio>
#include <iostream>

int main() {
    
  Map map;
  map.init(30, 80); // 之后要改为从地图初始化
  map.print();

  Player player;
  player.init(1, 1, 2, 1, 0);

  usleep(100000); // the unit is miu_s

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
