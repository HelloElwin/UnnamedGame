#include "elfin.h"
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
  
  sizecheck(); // check if the window size is big enough

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
        show_game_end(won, back, map_name);
      }
    } else if (choice == 1) { // about
      show_about(); // show about page 
    } else if (choice == 2) { // quit
      show_bye(); // show goodbye page
    }
  }

  return 0;
}


/* 
   initialize map and player and start the game
   input: the number of the map
   return value: true if the player wins the game, and false if loses
*/
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


/* 
   process the game, judge game status
   input: an object of class Map, an object of class Player
   return value: true for win and false for lose 
*/
bool game(Map& map, Player& player) {
  while (true) {
    char key = '.';
    if (kbhit()) key = get_keyboard();
    bool moving = false;
    player.move(key, map, moving);

    bool live_judge = true;
    live_judge = player.alive(map);

    bool touch_elfin = false;
    elfin_move(map, player, touch_elfin, moving);
    if (touch_elfin)
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
