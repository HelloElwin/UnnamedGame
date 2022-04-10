#include "utils.h"

#include <iostream>
#include <cstdio>
#include <termios.h>
#include <stdio.h>

// type sheet
// 0  air
// 1  ground
// 2  player
// 3  bar
// 4  gate 
// 5  world converter
// 6+ portal
 
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


void super_print(int Type) {
  int type = Type % 100;
  int property = Type / 100;
  /*if (type == 0) {
    printf(" ");
  } 
  else if (type == 1) {
    printf("\033[48;5;231m \033[0m");  
  } 
  else {
    switch (property) {
      case 'i':
        printf("\033[48;5;32m \033[0m");  
        break;
      case 'f':
        printf("\033[48;5;1m \033[0m");  
        break;
      case 'r':
        printf("\033[48;5;9m \033[0m");  
        break;
      case 'p':
        printf("\033[48;5;219m \033[0m");  
        break;
      case 'v':
        printf("\033[48;5;93m \033[0m");  
        break;
      case 'b':
        printf("\033[48;5;12m \033[0m");  
        break;
      case 'c':
        printf("\033[48;5;14m \033[0m");  
        break;
      case 'g':
        printf("\033[48;5;118m \033[0m");  
        break;
      case 'y':
        printf("\033[48;5;226m \033[0m");  
        break;
      case 'o':
        printf("\033[48;5;214m \033[0m");  
        break;
      case 'x':
        printf("\033[48;5;231m \033[0m");  
    }
  }
  */
  printf("\033[48;5;%dm \033[0m",property);
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

/*
int main() {
  int a;
  char b;
  while(true) {
    std::cin>>a>>b;
    super_print(a, b);
    printf("\n");
  }
  return 0;
}
*/
