#include "interface.h"
#include "utils.h"
#include "map.h"

#include <cstdio>
#include <string>
#include <iostream>

#define SQUARE_H 15
#define SQUARE_W 32
#define MAP_NUM 20
#define SINGLE_R 6
#define SINGLE_C 8

std::string background[MAP_R][MAP_C]; // background of each little map square
//0123456789 row: 6 column: 8
std::string number[10][MAP_R][MAP_C] = {
  {{"b", "█", "█", "█", "█", "█", "╗", "b"},{"█", "█", "b", "b", "b", "█", "█", "╗"},{"█", "█", "b", "b", "b", "█", "█", "║"},{"█", "█", "b", "b", "b", "█", "█", "║"},{"╚", "█", "█", "█", "█", "█", "╔", "╝"},{"b", "╚", "═", "═", "═", "═", "╝", "b"}},

  {{"b", "b", "b", "█", "█", "╗", "b", "b"},{"b", "b", "█", "█", "█", "║", "b", "b"},{"b", "b", "╚", "█", "█", "║", "b", "b"},{"b", "b", "b", "█", "█", "║", "b", "b"},{"b", "b", "b", "█", "█", "║", "b", "b"},{"b", "b", "b", "╚", "═", "╝", "b", "b"}}, 

  {{"█", "█", "█", "█", "█", "█", "╗", "b"},{"╚", "═", "═", "═", "═", "█", "█", "╗"},{"b", "█", "█", "█", "█", "█", "╔", "╝"},{"█", "█", "╔", "═", "═", "═", "╝", "b"},{"█", "█", "█", "█", "█", "█", "█", "╗"},{"╚", "═", "═", "═", "═", "═", "═", "╝"}},

  {{"█", "█", "█", "█", "█", "█", "╗", "b"},{"╚", "═", "═", "═", "═", "█", "█", "╗"},{"b", "█", "█", "█", "█", "█", "╔", "╝"},{"b", "╚", "═", "═", "═", "█", "█", "╗"},{"█", "█", "█", "█", "█", "█", "╔", "╝"},{"╚", "═", "═", "═", "═", "═", "╝", "b"}},

  {{"█", "█", "╗", "b", "b", "█", "█", "╗"},{"█", "█", "║", "b", "b", "█", "█", "║"},{"█", "█", "█", "█", "█", "█", "█", "║"},{"╚", "═", "═", "═", "═", "█", "█", "║"},{"b", "b", "b", "b", "b", "█", "█", "║"},{"b", "b", "b", "b", "b", "╚", "═", "╝"}},

  {{"█", "█", "█", "█", "█", "█", "█", "╗"},{"█", "█", "╔", "═", "═", "═", "═", "╝"},{"█", "█", "█", "█", "█", "█", "█", "╗"},{"╚", "═", "═", "═", "═", "█", "█", "║"},{"█", "█", "█", "█", "█", "█", "█", "║"},{"╚", "═", "═", "═", "═", "═", "═", "╝"}},

  {{"b", "█", "█", "█", "█", "█", "╗", "b"},{"█", "█", "╔", "═", "═", "═", "╝", "b"},{"█", "█", "█", "█", "█", "█", "╗", "b"},{"█", "█", "╔", "═", "═", "█", "█", "╗"},{"╚", "█", "█", "█", "█", "█", "╔", "╝"},{"b", "╚", "═", "═", "═", "═", "╝", "b"}},

  {{"█", "█", "█", "█", "█", "█", "█", "╗"},{"╚", "═", "═", "═", "═", "█", "█", "║"},{"b", "b", "b", "b", "█", "█", "╔", "╝"},{"b", "b", "b", "█", "█", "╔", "╝", "b"},{"b", "b", "b", "█", "█", "║", "b", "b"},{"b", "b", "b", "╚", "═", "╝", "b", "b"}},

  {{"b", "█", "█", "█", "█", "█", "╗", "b"},{"█", "█", "╔", "═", "═", "█", "█", "╗"},{"╚", "█", "█", "█", "█", "█", "╔", "╝"},{"█", "█", "╔", "═", "═", "█", "█", "╗"},{"╚", "█", "█", "█", "█", "█", "╔", "╝"},{"b", "╚", "═", "═", "═", "═", "╝", "b"}}, 

  {{"b", "█", "█", "█", "█", "█", "╗", "b"},{"█", "█", "╔", "═", "═", "█", "█", "╗"},{"╚", "█", "█", "█", "█", "█", "█", "║"},{"b", "╚", "═", "═", "═", "█", "█", "║"},{"b", "█", "█", "█", "█", "█", "╔", "╝"},{"b", "╚", "═", "═", "═", "═", "╝", "b"}}
}; 

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
  clear_screen();
  for (int i = 0; i < MAP_R; i++) {
    for (int j = 0; j < MAP_C; j++) {
      int color = 231;
      if (interface[i][j] == "█") printf("\033[48;5;%dm \033[0m", color);
      else printf("%s", interface[i][j].c_str());
    }
    printf("\n");
  }
}

void show_selection(int selection, std::string interface[][MAP_C]) {
  clear_screen();
  for (int i = 0; i < MAP_R; i++) {
    for (int j = 0; j < MAP_C; j++) {
      int color = 231;
      int bg = 8;
      int font = 2;
      int bgt = 100;
      bool selected = ((i / SQUARE_H == selection / (MAP_C / SQUARE_W)) && (j / SQUARE_W == selection % (MAP_C / SQUARE_W)));
      if (selected) {
        color = 8;
        bg = 15;
        font = 90;
        bgt = 107;
      }
      if (interface[i][j] == "█") 
        printf("\033[48;5;%dm \033[0m", color);
      else if (interface[i][j] == "b") 
        printf("\033[48;5;%dm \033[0m", bg);
      else if (interface[i][j] == " ") 
        printf("%s", interface[i][j].c_str());
      else 
        printf("\033[%d;%dm%s\033[m", font, bgt, interface[i][j].c_str());
    }
    printf("\n");
  }
}

void map_selection(std::string &selection) {
  int select = 0;
  int levnum = MAP_C / SQUARE_W;
  for (int i = 0; i < SQUARE_H - 2; i++)
    for (int j = 0; j < SQUARE_W - 2; j++)
      background[i][j] = "b";
  
  std::string interface[MAP_R][MAP_C];
  for (int i = 0; i < MAP_R; i++) {
    for (int j = 0; j < MAP_C; j++) {
      interface[i][j] = " ";
    }
  }
  for (int i = 0; i < MAP_NUM; i++) {
    draw_insert((i / levnum) * SQUARE_H + 1, (i % levnum) * SQUARE_W + 1, SQUARE_H - 2, SQUARE_W - 2, background, interface);
    if ((i + 1) / 10 == 0) {
      draw_insert((i / levnum) * SQUARE_H + (SQUARE_H - 2 - SINGLE_R) / 2 + 1, (i % levnum) * SQUARE_W + (SQUARE_W - SINGLE_C - 2) / 2 + 1, SINGLE_R, SINGLE_C, number[i + 1], interface);
    }
    else {
      int tens = (i + 1) / 10;
      int digits = (i + 1) % 10;
      std::string combine[MAP_R][MAP_C];
      for (int ii = 0; ii < SINGLE_R; ii++) {
        for (int j = 0; j < SINGLE_C; j++) {
          combine[ii][j] = number[tens][ii][j];
          combine[ii][SINGLE_C + j] = number[digits][ii][j];
        }
      }
      draw_insert((i / levnum) * SQUARE_H + (SQUARE_H - 2 - SINGLE_R) / 2 + 1, (i % levnum) * SQUARE_W + (SQUARE_W - SINGLE_C * 2 - 2) / 2 + 1, SINGLE_R, SINGLE_C * 2, combine, interface);
    }
  }
  draw_border((select / levnum) * SQUARE_H, (select % levnum) * SQUARE_W, SQUARE_H, SQUARE_W, interface); 
  show_selection(select, interface);
  char key = 'x';
  while (key != 'g') {
    for (int i = 0; i < MAP_R; i++) {
      for (int j = 0; j < MAP_C; j++) {
        interface[i][j] = " ";
      }
    }
    for (int i = 0; i < MAP_NUM; i++) {
      draw_insert((i / levnum) * SQUARE_H + 1, (i % levnum) * SQUARE_W + 1, SQUARE_H - 2, SQUARE_W - 2, background, interface);
      if ((i + 1) / 10 == 0) {
        draw_insert((i / levnum) * SQUARE_H + (SQUARE_H - 2 - SINGLE_R) / 2 + 1, (i % levnum) * SQUARE_W + (SQUARE_W - SINGLE_C - 2) / 2 + 1, SINGLE_R, SINGLE_C, number[i + 1], interface);
      }
      else {
        int tens = (i + 1) / 10;
        int digits = (i + 1) % 10;
        std::string combine[MAP_R][MAP_C];
        for (int ii = 0; ii < SINGLE_R; ii++) {
          for (int j = 0; j < SINGLE_C; j++) {
            combine[ii][j] = number[tens][ii][j];
            combine[ii][SINGLE_C + j] = number[digits][ii][j];
          }
        }
        draw_insert((i / levnum) * SQUARE_H + (SQUARE_H - 2 - SINGLE_R) / 2 + 1, (i % levnum) * SQUARE_W + (SQUARE_W - SINGLE_C * 2 - 2) / 2 + 1, SINGLE_R, SINGLE_C * 2, combine, interface);
      }
    }
    key = get_keyboard();
    switch(key) {
      case 'w':
        if (select / levnum == 0)
          break;
        select -= levnum;
        break;
      case 'a':
        if (select % levnum == 0)
          break;
        select -= 1;
        break;
      case 's':
        if (select / levnum == MAP_R / SQUARE_H - 1)
          break;
        select += levnum;
        break;
      case 'd':
        if (select % levnum == levnum - 1)
          break;
        select += 1;
        break;
    }
    draw_border((select / levnum) * SQUARE_H, (select % levnum) * SQUARE_W, SQUARE_H, SQUARE_W, interface); 
    show_selection(select, interface);
  }
  selection = std::to_string(select + 1);
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

