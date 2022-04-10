#include "map.h"
#include "utils.h"
#include "player.h"
#include "unistd.h"
#include "block_fill.h"

#include <cstdio>
#include <iostream>

void clear_screen() {
  printf("\033[2J\033[1;1H");
}


int welcome() {
  int x;
  clear_screen();
  printf("\033[1;97mWellcome to unnamed game!\n\033[0m");
  usleep(600000);
  printf("Please select a map from [1]\n");
  printf("Choice: ");
  scanf("%d", &x);
  return x;
}

int main() {
    
  int map_num = welcome();

  Map map;
  map.init(map_num); // map file No.1

  Player player;
  int cont0[4][10];
  fill(21, (int*)cont0);
  player.init(1, 2, 2, 2, 0,cont0);

  map.update(player);
  map.print();

  while (true) {
    
    char key = get_keyboard();

    player.move(key, map);
    
    map.check(player);
    map.update(player);

    clear_screen();
    map.print();

    // map.inspect(2);
    player.inspect(1);
     
    usleep(20000);
    
  }

  return 0;

}
