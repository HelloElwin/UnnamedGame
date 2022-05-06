#include "block_fill.h"
#include <fstream>
#include <string>

// content = color * 100 + property
// overall property = property(*10 + direction (if any)）

// overall_property of a portal:
// serial = overall_property / 10
// direction = overall % 10


/*
   fill the content
   input: 
    · int variable overall property
    · pointer pointing to int array content[5][10] 
    · int variable state indicating inner or outer
    · int array, storing a randonly generated portal colors
    no return value
*/
void fill(int overall, int *cont, int state, int portal_color[]) {
  const int row = 5;
  const int col = 10;

  const int grdwid = 1, grdlen = 10;
  const int perwid = 4, perlen = 4;
  const int elfinwid = 4, elfinlen = 2; 
  const int polwid1 = 2, pollen1 = 10;
  const int polwid2 = 2, pollen2 = 5;
  const int gatwid = 4, gatlen = 4;

  int *ct = cont;
  int GRD_C = 231;
  int AIR_C = 0;
  if (state == 1) {
    int temp;
    temp = GRD_C;
    GRD_C = AIR_C;
    AIR_C = temp;
  }

  int ELFIN_H = 4;
  int ELFIN_W = 6;

  //load the pre-saved template
  std::ifstream model1 ("./lib/blocks/1.txt");
  std::string temp1;
  std::string temp10;
  std::ifstream model3 ("./lib/blocks/3.txt");
  std::string temp3;
  std::ifstream model4 ("./lib/blocks/4.txt");
  std::string temp4;
  std::ifstream model51 ("./lib/blocks/51.txt");
  std::string temp51;
  std::ifstream model52 ("./lib/blocks/52.txt");
  std::string temp52;
  std::ifstream model61 ("./lib/blocks/61.txt");
  std::string temp61;
  std::ifstream model62 ("./lib/blocks/62.txt");
  std::string temp62;
  std::ifstream model63 ("./lib/blocks/63.txt");
  std::string temp63;
  std::ifstream model64 ("./lib/blocks/64.txt");
  std::string temp64;

  if (overall / 10 >= 6) { //portal
    int direct = overall % 10;
    int serial = overall / 10;
    int numcolor = GRD_C;
    int color_arr[8] = {9, 219, 93, 12, 14, 118, 226, 214}; 
    numcolor = color_arr[portal_color[serial - 6]];
    /*switch (serial) {
      case 6:
        numcolor = 9; //red
        break;
      case 7:
        numcolor = 219; //pink
        break;
      case 8:
        numcolor = 93; //violet
        break;
      case 9:
        numcolor = 12; //blue
        break;
      case 10:
        numcolor = 14; //cyan
        break;
      case 11:
        numcolor = 118; //green
        break;
      case 12:
        numcolor = 226; //yellow
        break;
      case 13:
        numcolor = 214; //orange
        break;
    }*/
    switch (direct) {
      case 1: // up
        while (getline (model61, temp61)) {
          for (int j = 0; j < col; j++) {
            if (temp61[j] == '2') // main body of portal
              *ct++ = numcolor * 100 + serial;
            else if (temp61[j] == '1') // ground
              *ct++ = GRD_C * 100 + 1;
            else // air
              *ct++ = AIR_C * 100 + 0;
          }
        }
        ct = cont;
        break;
      case 2: // down
        while (getline (model62, temp62)) {
          for (int j = 0; j < col; j++) {
            if (temp62[j] == '2')
              *ct++ = numcolor * 100 + serial;
            else if (temp62[j] == '1')
              *ct++ = GRD_C * 100 + 1;
            else
              *ct++ = AIR_C * 100 + 0;
          }
        }
        ct = cont;
        break;
      case 3: // left
        while (getline (model63, temp63)) {
          for (int j = 0; j < col; j++) {
            if (temp63[j] == '2')
              *ct++ = numcolor * 100 + serial;
            else if (temp63[j] == '1')
              *ct++ = GRD_C * 100 + 1;
            else
              *ct++ = AIR_C * 100 + 0;
          }
        }
        ct = cont;
        break;
      case 4: // right
        while (getline (model64, temp64)) {
          for (int j = 0; j < col; j++) {
            if (temp64[j] == '2')
              *ct++ = numcolor * 100 + serial;
            else if (temp64[j] == '1')
              *ct++ = GRD_C * 100 + 1;
            else
              *ct++ = AIR_C * 100 + 0;
          }
        }
        ct = cont;
        break;
    }
  }
  else if (overall / 10 >= 2) { // player and elfin and property ground and gravity converter
    int serial = overall / 10;
    int fi = overall % 10;
    int color = 0;
    switch(fi) {
      case 1: // ice
        color = 32;
        break;
      case 2: // fire
        color = 1;
        break;
    }
    switch(serial) {
      case 2: // property ground
        while (getline (model1, temp10)) {
          for (int j = 0; j < col; j++) {
            if (temp10[j] == '1')
              *ct++ = color * 100 + overall;
            else
              *ct++ = AIR_C * 100 + 0;
          }
        }
        ct = cont;
        break;
      case 3: // elfin
        while (getline(model3, temp3)) {
          for (int i = 0; i < ELFIN_W; i++) {
              if (temp3[i] == '1') 
                *ct++ = color * 100 + overall;
              else
                *ct++ = AIR_C * 100 + 0;
          }
        }
        ct = cont;
        break;
      case 5: // lower gravity converter
        if (fi == 1) {
          while (getline (model51, temp51)) {
            for (int j = 0; j < col; j++) {
              if (temp51[j] == '2')
                *ct++ = 21 * 100 + 5;
              else if (temp51[j] == '1')
                *ct++ = GRD_C * 100 + 1;
              else
                *ct++ = AIR_C * 100 + 0;
            }
          }
        }
        else { // upper gravity converter
          while (getline (model52, temp52)) {
            for (int j = 0; j < col; j++) {
              if (temp52[j] == '2')
                *ct++ = 21 * 100 + 5;
              else if (temp52[j] == '1')
                *ct++ = GRD_C * 100 + 1;
              else
                *ct++ = AIR_C * 100 + 0;
            }
          }
        }
        ct = cont;
        break;
    }
  }
  else { // not portal
    switch(overall) {
      case 0: //air
        for (int i = 0; i < row; i++) 
          for (int j = 0; j < col; j++)
            *ct++ = AIR_C * 100 + 0;
        break;
      case 1: // ground
        while (getline (model1, temp1)) {
          for (int j = 0; j < col; j++) {
            if (temp1[j] == '1')
              *ct++ = GRD_C * 100 + overall;
            else
              *ct++ = AIR_C * 100 + 0;
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
              *ct++ = GRD_C * 100 + 1;
            else
              *ct++ = AIR_C * 100 + 0;
          }
        }
        ct = cont;
        break;
    }
  }
  model1.close();
  model3.close();
  model4.close();
  model51.close();
  model52.close();
  model61.close();
  model62.close();
  model63.close();
  model64.close();
}


/*
   fill the content of the player
   input: int variable property, pointer pointing to an int array
   no return value
*/
void player_fill(int property, int *cont) {
  int color;
  switch(property) {
    case 1: // ice
      color = 32;
      break;
    case 2: // fire
      color = 1;
      break;
  }
  int *ct = cont;
  for (int i = 0; i < 2 * 2; i++) 
    *ct++ = color * 100 + 2;
}
