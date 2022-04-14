#include "map.h"
#include "utils.h"
#include "player.h"
#include "unistd.h"
#include "block_fill.h"
#include "../lib/maps/conio.h"
#include "windowsize.h"
#include "bar.h"

#include <cstdio>
#include <iostream>
#include <vector>

void clear_screen() {
  printf("\033[2J\033[1;1H");
}

void welcome() {
  clear_screen();
  printf("\033[1;97mWellcome to unnamed game!\n\033[0m");
  usleep(600000);
  sizecheck();
}

void print_maps() {
  printf("  [1]    The first journey\n");
  printf("  [2]    One taste of gravity\n");
  printf("  [3]    one taste of world converter\n");
  printf("  [4]    one taste of bar\n");
  printf("  [111]  You know what\n");
}

int choose_map() {
  int choice;
  clear_screen();
  printf("Please select a map from:\n");
  print_maps();
  printf("Choice: ");
  scanf("%d", &choice);
  return choice;
}

void death(int& map_num, bool& outcome) {
  clear_screen();
  printf("\033[1;31mGame Over\033[0m\n");
  usleep(1200000);
  printf("Do you want to continue?(Y/N): ");
  char choice1;
  scanf("%c", &choice1);
  while (choice1 != 'Y' && choice1 != 'N')
    scanf("%c", &choice1);
  if (choice1 == 'Y') {
    usleep(600000);
    printf("Do you wan to try the same map again?(Y/N): ");
    char choice2;
    scanf(" %c", &choice2);
    if (choice2 == 'Y')
      return;
    else {
      map_num = choose_map();
      return;
    }
  }
  else {
    outcome = false;
    printf("BYE!\n");
    usleep(1200000);
    return;
  }  
}

void success(int& map_num, bool& outcome) {
  clear_screen();
  printf("\033[1;33mSuccess!\033[0m\n");
  usleep(1200000);
  printf("Do you want to continue?(Y/N): ");
  char choice1;
  scanf("%c", &choice1);
  while (choice1 != 'Y' && choice1 != 'N')
    scanf("%c", &choice1);
  if (choice1 == 'Y') {
    usleep(600000);
    map_num = choose_map();
    return;
  }
  else {
    outcome = false;
    printf("BYE!\n");
    usleep(1200000);
    return;
  }
}

void begin(int& map_num, Map& map, Player& player) {
  clear_screen();
  map.init(map_num); 

  int cont0[2][2];
  //fill(21, (int*)cont0, 0);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++)
      cont0[i][j] = 0; 
  player.init(1, 2, 2, 2, 0,cont0, 2);

  map.update(player);
  map.print();
}

void game(int& map_num, Map& map, Player& player) {
  bool outcome = true;
  while (outcome) {
    
    char key = '.';
    if (kbhit()) key = get_keyboard();
    bool moving = false;
    player.move(key, map, moving);

    bool live_judge = true;
    live_judge = player.alive(map);

    bool touch_bar = false;
    bar_move(map, player, touch_bar, moving);
    if (touch_bar)
      live_judge = false;
    
    bool succ_judge = false;
    succ_judge = player.success(map);

    if (!live_judge) {
      map.bars.clear();
      usleep(300000);
      death(map_num, outcome);
      if (outcome)
        begin(map_num, map, player);
      continue;
    }

    if (succ_judge) {
      usleep(300000);
      success(map_num, outcome);
      if (outcome)
        begin(map_num, map, player);
      continue;
    }

    map.check(player);
    map.update(player);

    if (moving) {
      clear_screen();
      map.print();
      //map.inspect(3);
      player.inspect(1);
    }

     
    usleep(50000);

  }
}

int main() {

  Map map;
  Player player;

  int map_num;
  welcome();
  map_num = choose_map();

  begin(map_num, map, player);
  game(map_num, map, player);

  return 0;
}
