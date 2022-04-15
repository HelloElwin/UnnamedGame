#include <cstdio>
#include "interface.h"

void clear_screen() {
  printf("\033[2J\033[1;1H");
}
