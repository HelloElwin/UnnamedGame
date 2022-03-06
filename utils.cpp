#include "utils.h"

#include <iostream>
#include <cstdio>
#include <termios.h>
#include <stdio.h>

// type sheet
// 0    air
// 1    ground

void super_print(int type) {
  switch (type) {
    case 0:
      std::cout << " ";
      break;
    case 1:
      std::cout << "\u2588";
      break;
  }
  // printf("\033[0;30;43m Hello \033[0m");
}
 
// Adapted from https://zhuanlan.zhihu.com/p/381561249
char get_keyboard(void) {
    char input;
    struct termios new_settings;
    struct termios stored_settings;
    tcgetattr(0,&stored_settings);
    new_settings = stored_settings;
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_cc[VTIME] = 0;
    tcgetattr(0,&stored_settings);
    new_settings.c_cc[VMIN] = 1;
    tcsetattr(0,TCSANOW,&new_settings);

    input = getchar();

    tcsetattr(0,TCSANOW,&stored_settings);
    return input;
}
