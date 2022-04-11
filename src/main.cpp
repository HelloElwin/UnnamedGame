#include "map.h"
#include "utils.h"
#include "player.h"
#include "unistd.h"
#include "block_fill.h"
#include "../lib/maps/conio.h"

#include <cstdio>
#include <iostream>

void clear_screen() {
  printf("\033[2J\033[1;1H");
}

void welcome() {
  clear_screen();
  printf("\033[1;97mWellcome to unnamed game!\n\033[0m");
  usleep(600000);
}

int choose_map() {
  int choice;
  printf("Please select a map from [1 / 11 / 111]\n");
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

void begin(int& map_num, Map& map, Player& player) {
  clear_screen();
  map.init(map_num); // map file No.1

  int cont0[4][10];
  fill(21, (int*)cont0);
  player.init(1, 2, 2, 2, 0,cont0, 1);

  map.update(player);
  map.print();
}

void game(int& map_num, Map& map, Player& player) {
  bool outcome = true;
  while (outcome) {
    
    char key = '.';
    if (kbhit()) key = get_keyboard();
    player.move(key, map);

    bool judge = true;
    judge = player.alive(map);
    char temp;
    if (!judge) {
      usleep(300000);
      death(map_num, outcome);
      if (outcome)
        begin(map_num, map, player);
      continue;
    }

    map.check(player);
    map.update(player);

    clear_screen();
    map.print();

    //map.inspect(2);
    player.inspect(1);
     
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
