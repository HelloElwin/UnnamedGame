#include "bar.h"
#include "map.h"
#include "utils.h"
#include "player.h"
#include "unistd.h"
#include "interface.h"
#include "block_fill.h"
#include "../lib/maps/conio.h"

#include <cstdio>
#include <vector>
#include <string>
#include <iostream>

bool game(Map&, Player&);
bool start_game(std::string);

int main() {
  
  sizecheck();

  int choice = -1;
  while (choice != 2) {
    show_welcome(choice);
    if (choice == 0) { // start
      std::string map_name = "Not selected yet!";
      map_selection(map_name);
      bool back = false;
      while (!back) {
        printf("Selected map: %s", map_name.c_str());
        bool won = start_game(map_name);
        show_game_end(won, back);
      }
    } else if (choice == 1) { // about
      // show about 
    } else if (choice == 2) { // quit
      // show goodbye
    }
  }

  return 0;
}

bool start_game(std::string map_name) {
  Player player;
  clear_screen();
  int player_cont[2][2];
  int player_property=2;
  player_fill(player_property, (int*)player_cont);
  player.init(1, 2, 2, 2, 0, player_cont, player_property);

  Map map;
  map.init(std::stoi(map_name)); // assume map name is an integer
  map.update(player);
  map.print();

  return game(map, player);
}

bool game(Map& map, Player& player) {
  while (true) {
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

    if (!live_judge) return false;
    if (succ_judge) return true;

    map.check(player);
    map.update(player);

    if (moving) {
      clear_screen();
      map.print();
      // map.inspect(3);
      player.inspect(1);
    }
     
    usleep(50000);
  }
}

/*

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
*/
