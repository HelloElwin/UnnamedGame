#include "block_fill.h"
#include <fstream>
#include <string>

// content = color的int*100+属性的数字
// overall property = 属性*10+方向/冰火（如果有）

// overall_property of a portal
// serial = overall_property / 10
// direction = overall % 10

void fill(int overall, int *cont) {
  const int row = 5;
  const int col = 10;

  const int grdwid = 1, grdlen = 10;
  const int perwid = 4, perlen = 4;
  const int barwid = 4, barlen = 2; 
  const int polwid1 = 2, pollen1 = 10;
  const int polwid2 = 2, pollen2 = 5;
  const int gatwid = 4, gatlen = 4;

  int *ct = cont;
  
  std::ifstream model1 ("./lib/blocks/1.txt");
  std::string temp1;
  std::ifstream model4 ("./lib/blocks/4.txt");
  std::string temp4;
  std::ifstream model51 ("./lib/blocks/51.txt");
  std::string temp51;
  std::ifstream model52 ("./lib/blocks/52.txt");
  std::string temp52;
  std::ifstream model53 ("./lib/blocks/53.txt");
  std::string temp53;
  std::ifstream model54 ("./lib/blocks/54.txt");
  std::string temp54;

  if (overall / 10 >= 5) { //portal
    int direct = overall % 10;
    int serial = overall / 10;
    int numcolor = 231;
    switch (serial) {
      case 5:
        numcolor = 9; //red
        break;
      case 6:
        numcolor = 219; //pink
        break;
      case 7:
        numcolor = 93; //violet
        break;
      case 8:
        numcolor = 12; //blue
        break;
      case 9:
        numcolor = 14; //cyan
        break;
      case 10:
        numcolor = 118; //green
        break;
      case 11:
        numcolor = 226; //yellow
        break;
      case 12:
        numcolor = 214; //orange
        break;
    }
    switch (direct) {
      case 1: //up
        while (getline (model51, temp51)) {
          for (int j = 0; j < col; j++) {
            if (temp51[j] == '2')
              *ct++ = numcolor * 100 + serial;
            else if (temp51[j] == '1')
              *ct++ = 23101;
            else
              *ct++ = 0;
          }
        }
        ct = cont;
        break;
      case 2: //down
        while (getline (model52, temp52)) {
          for (int j = 0; j < col; j++) {
            if (temp52[j] == '2')
              *ct++ = numcolor * 100 + serial;
            else if (temp52[j] == '1')
              *ct++ = 23101;
            else
              *ct++ = 0;
          }
        }
        ct = cont;
        break;
      case 3: //left
        while (getline (model53, temp53)) {
          for (int j = 0; j < col; j++) {
            if (temp53[j] == '2')
              *ct++ = numcolor * 100 + serial;
            else if (temp53[j] == '1')
              *ct++ = 23101;
            else
              *ct++ = 0;
          }
        }
        ct = cont;
        break;
      case 4: //right
        while (getline (model54, temp54)) {
          for (int j = 0; j < col; j++) {
            if (temp54[j] == '2')
              *ct++ = numcolor * 100 + serial;
            else if (temp54[j] == '1')
              *ct++ = 23101;
            else
              *ct++ = 0;
          }
        }
        ct = cont;
        break;
    }
  }
  else if (overall / 10 > 0) { //player and bar
    int p = overall / 10;
    int fi = overall % 10;
    int color = 0;
    switch(fi) {
      case 1: //ice
        color = 32;
        break;
      case 2: //fire
        color = 1;
        break;
    }
    //to be continued
  }
  else { //not portal
    switch(overall) {
      case 0: //air
        for (int i = 0; i < row; i++) 
          for (int j = 0; j < col; j++)
            *ct++ = 0;
        break;
      case 1: //ground
        while (getline (model1, temp1)) {
          for (int j = 0; j < col; j++) {
            if (temp1[j] == '1')
              *ct++ = 231 * 100 + overall;
            else
              *ct++ = 0;
          }
        }
        ct = cont;
        break;
      case 4: // gate
        while (getline (model4, temp4)) {
          for (int j = 0; j < col; j++) {
            if (temp4[j] == '2')
              *ct++ = 131 * 100 + overall;
            else if (temp4[j] == '1')
              *ct++ = 23101;
            else
              *ct++ = 0;
          }
        }
        ct = cont;
        break;
    }
  }
  model1.close();
  model4.close();
  model51.close();
  model52.close();
  model53.close();
  model54.close();
}
/*design test

  int content = 0;
  for (int i = 1;i <= 60;i++) {
    for(int j = 1; j <= 160;j++) {
      content = (i == 1)||(i == 60) ? 1 : 0;

      //portal
      //up pink
      if(i >= 38 && i <= 41 && j >= 40 && j <= 49)
        content = 3;
      if((i == 40 && j >= 40 && j <= 49)||(i == 39 && (j == 40 || j == 41 || j == 48 || j ==49)))
        content = 4;
      //down violet
      if(i >= 38 && i <= 41 && j >= 70 && j <= 79)
        content = 3;
      if((i == 39 && j >= 70 && j <= 79)||(i == 40 && (j == 70 || j == 71 || j == 78 || j ==79)))
        content = 5;
      //left cyan
      if(i <= 41 && i >= 38 && j >= 101 && j <= 110)
        content = 3;
      if(((i <= 41 && i >= 38) && j == 105)||((i == 41 || i == 38) && (j == 106)))
        content = 6;

      //right green
      if(i <= 35 && i >= 32 && j >= 101 && j <= 110)
        content = 3;
      if(((i <= 35 && i >= 32) && j == 106)||((i == 35 || i == 32) && (j == 105)))
        content = 7;

      //gate 131
      if (i >= 20 && i <= 23 && j >= 101 && j<=110)
        content = 3;
      if ((i >= 20 && i <= 23 && j >=105 && j <= 106)||((i == 22 || i == 23) && (j == 104 || j == 107)))
        content = 8;

      //ground 231
      if (i >= 20 && i <=23 && j >= 70 && j<= 79)
        content = 3;
      if (i == 23 && j >= 70 && j <=79)
        content = 9;

      //player ice
      if (i >= 20 && i <= 23 && j >= 41 && j <= 50)
        content = 3;
      if (((i == 20 || i == 22 || i == 23) && j >= 44 && j <= 47)||(i == 21 && j >= 45 && j <= 46))
        content = 10;

      //bar fire
      if (i <= 35 && i >= 32 && j <= 50 && j >= 41)
        content = 3;
      if (i <= 35 && i >= 32 && j >= 45 && j <= 46)
        content = 11;

      switch (content) {
        case 0:
          printf(" ");
          break;
        case 1:
          printf("\033[48;5;231m \033[0m");
          break;
        case 2:
          printf("\033[48;5;135m \033[0m");
          break;
        case 3:
          printf("\033[48;5;230m \033[0m");
          break;
        case 4:
          printf("\033[48;5;219m \033[0m");
          break;
        case 5:
          printf("\033[48;5;93m \033[0m");
          break;
        case 6:
          printf("\033[48;5;14m \033[0m");
          break;
        case 7:
          printf("\033[48;5;118m \033[0m");
          break;
        case 8:
          printf("\033[48;5;131m \033[0m");
          break;
        case 9:
          printf("\033[48;5;231m \033[0m");
          break;
        case 10:
          printf("\033[48;5;32m \033[0m");
          break;
        case 11:
          printf("\033[48;5;1m \033[0m");
          break;
      }
    }
    printf("\n");
  }
}
}
*/
