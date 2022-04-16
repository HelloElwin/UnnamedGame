#include "interface.h"
#include "utils.h"
#include "map.h"

#include <cstdio>
#include <string>
#include <iostream>

void show_welcome(int* choice) {
  std::string welcome_msg = "Welcome to the Unnamed Game!";
  std::string tip_msg = "Press WASD to move; Press g to select";
  int pos = 0;
  char key = 'x';
  while (key != 'g') {
    clear_screen();
    std::string interface[MAP_R][MAP_C];
    draw_initial_interface(interface);
    draw_words(20, 60, welcome_msg, interface);
    draw_words(55, 60, tip_msg, interface);
    draw_words(30, 60, "Start", interface);
    draw_words(35, 60, "Help", interface);
    draw_words(40, 60, "Help", interface);
    switch (key) {
      case 'w':
        if (pos != 0) pos -= 1;
        break;
      case 's':
        if (pos != 2) pos += 1;
    }
    if (pos == 0) draw_border(29, 59, 3, 7, interface);
    else if (pos == 1) draw_border(34, 59, 3, 6, interface);
    else if (pos == 2) draw_border(39, 59, 3, 6, interface);
    show_interface(interface);
    key = get_keyboard();
  }
  *choice = pos;
}

void show_interface(std::string interface[][MAP_C]) {
  for (int i = 0; i < MAP_R; i++) {
    for (int j = 0; j < MAP_C; j++) {
      int color = 231;
      if (interface[i][j] == "█") printf("\033[48;5;%dm \033[0m", color);
      else std::cout << interface[i][j];
    }
    std::cout << '\n';
  }
}

void draw_initial_interface(std::string interface[][MAP_C]) {
  int r = MAP_R;
  int c = MAP_C;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (i == r - 1 && j == c - 1) interface[i][j] = "╝";
      else if (i == r - 1 && j == 0) interface[i][j] = "╚";
      else if (i == 0 && j == c - 1) interface[i][j] = "╗";
      else if (i == 0 && j == 0) interface[i][j] = "╔";
      else if (j == 0 || j == c - 1) interface[i][j] = "║";
      else if (i == 0 || i == r - 1) interface[i][j] = "═";
      else interface[i][j] = " ";
    }
  }
}

void draw_border(int x, int y, int r, int c, std::string interface[][MAP_C]) {
  for (int i = 0; i < r; i++) 
    for (int j = 0; j < c; j++) 
      if (i == r - 1 && j == c - 1) interface[x + i][y + j] = "╝";
      else if (i == r - 1 && j == 0) interface[x + i][y + j] = "╚";
      else if (i == 0 && j == c - 1) interface[x + i][y + j] = "╗";
      else if (i == 0 && j == 0) interface[x + i][y + j] = "╔";
      else if (j == 0 || j == c - 1) interface[x + i][y + j] = "║";
      else if (i == 0 || i == r - 1) interface[x + i][y + j] = "═";
      else continue;
}

void draw_box(int x, int y, int r, int c, std::string interface[][120]) {
  for (int i = 0; i < r; i++) 
    for (int j = 0; j < c; j++) 
      interface[x + i][y + j] = "█";
}

void draw_insert(int x, int y, int r, int c, std::string pattern[][MAP_C], std::string interface[][MAP_C]) {
  for (int i = 0; i < r; i++) 
    for (int j = 0; j < c; j++) 
      interface[x + i][y + j] = pattern[i][j];
}

void draw_words(int x, int y, std::string words, std::string interface[][MAP_C]) {
  for (int i = 0; i < words.size(); i++)
    interface[x][y + i] = words[i];
}

void clear_screen() {
  printf("\033[2J\033[1;1H");
}
