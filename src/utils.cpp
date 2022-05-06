#include "utils.h"

#include <sys/ioctl.h>
#include <termios.h>
#include <iostream>
#include <unistd.h>
#include <cstdio>

// type sheet
// 0        air
// 1        ground
// 21       ice ground
// 22       fire ground
// 31       ice bar
// 32       fire bar
// 4        gate 
// 5        world converter
// 6 - 13   portal
 
// property sheet
// property = 'x' : none
// property = 'i' : ice 32
// property = 'f' : fire 1
// property = 'r' : red 9
// property = 'p' : pink 219
// property = 'v' : violet 93
// property = 'b' : blue 12
// property = 'c' : cyan 14
// property = 'g' : green 118
// property = 'y' : yellow 226
// property = 'o' : orange 214


/*
   print according to the property
   input: int variable Type = color * 100 + property
   no return value
*/
void super_print(int Type) {
  int property = Type / 100;
  printf("\033[48;5;%dm \033[0m",property);
}


/* 
   Adapted from https://zhuanlan.zhihu.com/p/381561249
   minitor real-time keyboard input
   no input
   return value: char variable, the keyboard input
*/
char get_keyboard(void) {
  char input;
  struct termios new_settings;
  struct termios stored_settings;
  tcgetattr(0, &stored_settings);
  new_settings = stored_settings;
  new_settings.c_lflag &= (~ICANON);
  new_settings.c_cc[VTIME] = 0;
  tcgetattr(0, &stored_settings);
  new_settings.c_cc[VMIN] = 1;
  tcsetattr(0, TCSANOW, &new_settings);

  input = getchar();

  tcsetattr(0, TCSANOW, &stored_settings);
  return input;
}


/*
   check if the current window size is big enough
   no input
   no return value
*/
void sizecheck(void) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int row = w.ws_row;
    int col = w.ws_col;

    while (row < 60 || col < 160) {
      if (col < 160) {
        printf("Your current window size could only contain %d columns. Please enlarge your window.\n\n", col);
        usleep(600000);
        while (col == w.ws_col) {
          ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        }
      }
      if (row < 60) {
        printf("Your current window size could only contain %d lines. Please enlarge your window.\n\n", row);
        usleep(600000);
        while (row == w.ws_row) {
          ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        }
      }
      row = w.ws_row;
      col = w.ws_col;
    }

    return;  
}
