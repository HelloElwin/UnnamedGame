#include <cstdio>
int main() {
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

      //elfin fire
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

