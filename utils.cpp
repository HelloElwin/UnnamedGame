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
// 4  portal
// 5  gate
 
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


void super_print(int type, char propty) {
  switch (type) {
    case 0:
      printf(" ");
      break;
    case 1:
      printf("\033[48;5;231m \033[0m");  
      break;
    case 2:
    case 3:
    case 4:
    case 5:
      switch (propty) {
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
      }
  }
  // printf("\033[0;30;43m Hello \033[0m");
}
/*int main() {
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
