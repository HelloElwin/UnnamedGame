#include <cstdio>
#include <string>

#ifndef HEADER_INTERFACE
#define HEADER_INTERFACE

void show_welcome(void); // adjust window size and show game logo
void show_map_selection(std::string*); // (return map_name) select a map with WASD and then show_game will be called
void show_game(std::string, int*); // (map_name, return game_outcome), start a game on a map
void show_game_end(int, std::string); // (0 for lose 1 for win, map_name), show win or lose, and choose to continue on same map / another map / quit

void draw_initial_interface(char*); // (return an empty interface) draw an empty interface with borders
void draw_box(int, int, int, int, char*); // (row, col, height, width, interface), draw a square on a given interface
void draw_insert(int, int, char*, char*); // (row, col, stuff to be inserted, interface), insert a pattern to a given interface

void clear_screen(void); // clear screen

#endif

