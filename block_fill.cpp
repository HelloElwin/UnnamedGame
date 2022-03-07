#include "block_fill.h"
void fill(int overall, int *cont) {
  const int row = 4;
  const int col = 10;

  const int grdwid = 1, grdlen = 10;
  const int perwid = 4, perlen = 4;
  const int barwid = 4, barlen = 2; 
  const int polwid1 = 2, pollen1 = 10;
  const int polwid2 = 2, pollen2 = 4;
  const int gatwid = 4, gatlen = 4;

  int *ct = cont;
//  int *pty = propty;

  if(overall/100 > 0 || overall/10 >= 5) { //portal
    int direct = overall % 10;
    int color = overall / 10;
    int numcolor = 231;
    switch (color) {
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
        for (int i = 1; i <= col * (row - polwid1); i++) {
          *ct++ = 0;
        }
        *ct++ = numcolor * 100 + color;
        for (int i = 1; i <= pollen1 - 2; i++) {
          *ct++ = 0;
        }
        *ct++ = numcolor * 100 + color;
        for (int i = 1; i <= col - pollen1; i++) {
          *ct++ = 0;
        }
        for (int j = 1; j <= polwid1 -1; j++) {
          for (int i = 1; i <= pollen1; i++) {
            *ct++ = numcolor * 100 + color;
          } 
          for (int i = 1; i <= col - pollen1; i++) {
            *ct++ = 0;
          }
        }
        ct = cont;
        break;
      case 2: //down
        for (int i = 1; i <= col * (row - polwid1); i++) {
          *ct++ = 0;
        }
        for (int j = 1; j <= polwid1 -1; j++) {
          for (int i = 1; i <= pollen1; i++) {
            *ct++ = numcolor * 100 + color;
          } 
          for (int i = 1; i <= col - pollen1; i++) {
            *ct++ = 0;
          }
        }
        *ct++ = numcolor * 100 + color;
        for (int i = 1; i <= pollen1 - 2; i++) {
          *ct++ = 0;
        }
        *ct++ = numcolor * 100 + color;
        for (int i = 1; i <= col - pollen1; i++) {
          *ct++ = 0;
        }
        ct = cont;
        break;
      case 3: //left
        for (int j = 1; j <= polwid2-1; j++) {
          for (int i = 1; i <= pollen2; i++) {
            *ct = numcolor * 100 + color;
            ct = ct + col; 
          } 
          for (int i = 1; i <= row - pollen2; i++) {
            *ct = 0;
            ct = ct + col;
          }
          ct = cont + j;
        }
        *ct = numcolor * 100 + color;
        for (int i = 1; i <= pollen2 - 2; i++) {
          ct = ct + col;
          *ct = 0;
        }
        ct = ct + col;
        *ct = numcolor * 100 + color;
        for (int i = 1; i <= row - pollen2; i++) {
          ct = ct + col;
          *ct = 0;
        }
        for (int i = polwid2; i <= col - 1; i++) {
          ct = cont + i;
          for (int j = 1; j <= row; j++) {
            *ct = 0;
            ct = ct + col;
          }
        }
        ct = cont;
        break;
      case 4: //right
        *ct = numcolor * 100 + color;
        for (int i = 1; i <= pollen2 - 2; i++) {
          ct = ct + col;
          *ct = 0;
        }
        ct = ct + col;
        *ct = numcolor * 100 + color;
        for (int i = 1; i <= row - pollen2; i++) {
          ct = ct + col;
          *ct = 0;
        }
        for (int j = 1; j <= polwid2 - 1; j++) {
          ct = cont + j;
          for (int i = 1; i <= pollen2; i++) {
            *ct = numcolor * 100 + color;
            ct = ct + col; 
          } 
          for (int i = 1; i <= row - pollen2; i++) {
            *ct = 0;
            ct = ct + col;
          }
        }
        for (int i = polwid2; i <= col - 1; i++) {
          ct = cont + i;
          for (int j = 1; j <= row; j++) {
            *ct = 0;
            ct = ct + col;
          }
        }
        ct = cont;
        break;
    }
  }
  else if (overall/10 > 0) {
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
    switch(p) {
      case 2: //player
        for (int i = 1; i <= row - perwid; i++) {
          for (int j = 1; j <= col; j++) {
            *ct++ = 0;
          }
        }
        for (int i = 1; i <= perlen; i++) {
          *ct++ = color * 100 + p;
        }
        for (int i = 1; i <= col - perlen; i++) {
          *ct++ = 0;
        }
        for (int i = 1; i <= perlen/4;i++) {
          *ct++ = 0;
        }
        for (int i = 1; i <= perlen - (perlen/4)*2; i++) {
          *ct++ = color * 100 + p;
        }
        for (int i = 1; i <= col - perlen + perlen/4; i++) {
          *ct++ =0;
        }
        for (int i = 1; i <= perwid - 2; i++) {
          for (int j = 1; j <= perlen; j++) {
            *ct++ = color * 100 + p;
          }
          for (int j = 1; j <= col - perlen; j++) {
            *ct++ = 0;
          }
        }
        ct = cont;
        break;
        
      case 3: // bar
        for (int j = 1; j <= barlen; j++) {
          for (int i = 1; i <= barwid; i++) {
            *ct = color * 100 + p;
            ct = ct + col;
          }
          ct = cont + j;
        }
        for (int i = barlen; i <= col - 1; i++) {
          ct = cont + i;
          for (int j = 1; j <= row; j++) {
            *ct = 0;
            ct = ct + col;
          }
        }
        ct = cont;
        break;
      
    }
  }
  else { //not portal
    switch(overall) {
      case 1: //ground
        for (int i = 1; i <= row - grdwid; i++) {
          *ct++ = 0;
        }
        for (int j = 1; j <= grdwid; j++) {
          for (int i = 1; i <= grdlen; i++) {
            *ct++ = 23100 + overall;
          }
        }
        ct = cont;
        break;
      case 4: // gate
        for (int j = 1; j <= gatlen/4; j++) {
          for (int i = 1; i <= row - gatwid/2; i++) {
            *ct = 0;
            ct = ct + col;
          }
          for (int i = 1; i <= gatwid/2; i++) {
            *ct = 13100 + overall;
            ct = ct + col;
          }
          ct = cont + j;
        }
        for (int i = gatlen/4; i <= gatlen/4 + gatlen/2 - 1; i++) {
          ct = cont + i;
          for (int j = 1; j <= row - gatwid; j++) {
            *ct = 0;
            ct = ct + col;
          }
          for (int j = 1; j <= gatwid; j++) {
            *ct = 13100 + overall;
            ct = ct + col;
          }
        }
        ct = cont + gatlen/4 + gatlen/2;
        for (int j = 1; j <= gatlen/4; j++) {
          for (int i = 1; i <= row - gatwid/2; i++) {
            *ct = 0;
            ct = ct + col;
          }
          for (int i = 1; i <= gatwid/2; i++) {
            *ct = 13100 + overall;
            ct = ct + col;
          }
          ct = ct + j;
        }
        for (int i = gatwid; i <= col - 1; i++) {
          ct = cont + i;
          for (int j = 1; j <= row; j++) {
            *ct = 0;
            ct = ct + col;
          }
        }
        break;
    }
  }
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
