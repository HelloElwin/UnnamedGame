#include "blocks.h"

#include <vector>

// class Block {
//   public:
//     void init(int, int, int[], char[]);
//     void move(char, Map&)
//     int x, y;
//     int last_x, last_y;
//     int content[4][10];
//     int overall_property;
//     char property[4][10];
// };

void Block::init(int x0, int y0, int cont[][10], char prop[][10], int p0) {
  x = last_x = x0;
  y = last_y = y0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 10; j++) {
      content[i][j] = cont[i][j];
      property[i][j] = prop[i][j];
    }
  }
  overall_property = p0;
}

int get_portal(int tar, std::vector<Block> blocks) {
  for (int i = 0; i < blocks.size(); i++) {
    if (blocks[i].overall_property == tar) {
      return blocks[i].x;
    }
  }
  return 0;
}
