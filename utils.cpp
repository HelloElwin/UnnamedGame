#include "utils.h"

#include <iostream>
#include <cstdio>

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
