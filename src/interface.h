#include <cstdio>
#include <string>

#ifndef HEADER_INTERFACE
#define HEADER_INTERFACE

#include "map.h"

void show_welcome(int*); // adjust window size and show game logo
void map_selection(std::string&); // (return map_name) select a map with WASD and then show_game will be called
void show_selection(int, std::string[][MAP_C]); //print function of map_selection
void show_game(std::string, int*); // (map_name, return game_outcome), start a game on a map
void show_game_end(int, std::string); // (0 for lose 1 for win, map_name), show win or lose, and choose to continue on same map / another map / quit
void show_interface(std::string[][MAP_C]);

void draw_initial_interface(std::string[][MAP_C]); // (return an empty interface) draw an empty interface with borders
void draw_box(int, int, int, int, std::string[][MAP_C]); // (row, col, height, width, interface), draw a square on a given interface
void draw_insert(int, int, int, int, std::string pattern[][MAP_C], std::string interface[][MAP_C]); // (row, col, h, w, stuff to be inserted, interface), insert a pattern to a given interface
void draw_border(int x, int y, int r, int c, std::string interface[][MAP_C]);
void draw_words(int x, int y, std::string words, std::string interface[][MAP_C]);

void clear_screen(void); // clear screen

#endif

