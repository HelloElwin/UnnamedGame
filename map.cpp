#include "map.h"
#include "utils.h"

#include <cstdio>
#include <iostream>

// class Map {
//   public:
//     void init(int, int);
//     void print(void);
//     void update(void);
//   private:
//     int row;
//     int col;
//     int state;
//     map content[200][200];
// };

void Map::init(int r, int c) {
  row = r;
  col = c;
  state = 0;
  for (int i = 0; i < r; i++)
    for (int j = 0; j < c; j++)
      content[i][j] = ((i == 0 || i == r - 1) ? 1 : 0);
}

void Map::print(void) {
  for (int i = row - 1; i >= 0; i--) {
    for (int j = 0; j < col; j++) {
      super_print(content[i][j]); // 在utils里，输出特定“像素”
    }
    printf("\n");
  }
}

void Map::update(void) {
  printf("Nothing");
}
