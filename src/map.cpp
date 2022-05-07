#include "map.h"
#include "utils.h"
#include "player.h"
#include "block_fill.h"
#include "elfin.h"

#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>

// class Block {
//   public:
//     void init(int, int[]);
//     int x, y;
//     int overall_property;
//     int content[BLOCK_H][BLOCK_W];
// };
// 
// class Map {
//   public:
//     void init(int);
//     void print(void);
//     void inspect(int);
//     void check(Player&);
//     void update(Player);
//     void converter(Player&);
//     Block get_tar_portal(int, int, int, bool&);
//     int content[MAP_R][MAP_C];
// 	   int portal_color[8];
//     Block blocks[MAP_H][MAP_W];
//     int gravity; // verticle gravity only
//     std::vector<Elfin> elfins;
// };


/* 
   fill the block content[5][10] and attach property
   input: int variable, property of the block; int array, storing the randomly generated arrangement of portal colors
   no return value
*/
void Block::init(int property, int portal_color[]) {
  fill(property, (int*)content, 0, portal_color);
  overall_property = property;
}


/*
   print the properties (and contents) of all blocks/the map, for debugging
   input: int value indicating the debugging level
   no return value
*/
void Map::inspect(int level) {
  if (level >= 1) {
    for (int i = 0; i < MAP_H; i++) {
      for (int j = 0; j < MAP_W; j++)
        printf("%d  ", blocks[i][j].overall_property);
      printf("\n");
    }
  }
  if (level >= 2) {
    for (int i = 0; i < MAP_R; i++) {
      for (int j = 0; j < MAP_C; j++)
        printf("%d ", content[i][j]);
      printf("\n");
    }
  }
}


/*
   fill all blocks with corresponding properties according to the pre-saved specific map file
   input: the map number
   no return value
*/
void Map::init(int map_num) {

  for (int i = 0; i < MAP_R; i++)
    for (int j = 0; j < MAP_C; j++)
      content[i][j] = 0;

  std::string path = "lib/maps/" + std::to_string(map_num) + ".txt";
  std::ifstream map_file(path);

  for (int i = MAP_H - 1; i >= 0; i--) {
    for (int j = 0; j < MAP_W; j++) {
      int serial;
      int temp;
      char x;
      map_file >> x;
      if (x == '\n') map_file >> x;
      switch (x) {
        case '0':
          blocks[i][j].overall_property = 0;
          break;
        case '#': // ground
          blocks[i][j].overall_property = 1;
          break;
        case '(': // up portal
          map_file >> serial >> x;
          blocks[i][j].overall_property = serial * 10 + 1;
          break;
        case ')': // down portal
          map_file >> serial >> x;
          blocks[i][j].overall_property = serial * 10 + 2;
          break;
        case '[': // left portal
          map_file >> serial >> x;
          blocks[i][j].overall_property = serial * 10 + 3;
          break;
        case ']': // right portal
          map_file >> serial >> x;
          blocks[i][j].overall_property = serial * 10 + 4;
          break;
        case '|': // gate
          blocks[i][j].overall_property = 4;
          break;
        case 'i': // ice ground
          blocks[i][j].overall_property = 21;
          break;
        case 'f': // fire ground
          blocks[i][j].overall_property = 22;
          break;
        case 'g': // lower gravity-converter
          blocks[i][j].overall_property = 51;
          break;
        case 'G': // upper gravity-converter
          blocks[i][j].overall_property = 52;
          break;
        case 'b': // elfin
          map_file >> serial >> x;
          Elfin elfin;
          int content[4][6];
          fill(serial, (int*)content, 0, portal_color);
          elfin.init(i * BLOCK_H + 2, j * BLOCK_W + 4, 4, 6, content, serial, i);
          elfins.push_back(elfin);
          blocks[i][j].overall_property = 1;
          break;
      }
    }
  }

  map_file.close();

  //generate a random arrangement of portal colors
  bool judge_repeat[8];
  for (int i = 0; i < 8; i++)
    judge_repeat[i] = false;
  srand(time(NULL));
  for (int i = 0; i < 8; i++) {
    int c = rand() % 8;
    while(judge_repeat[c])
      c = rand() % 8;
    judge_repeat[c] = true;
    portal_color[i] = c;
  }

  for (int i = 0; i < MAP_H; i++)
    for (int j = 0; j < MAP_W; j++) {
      blocks[i][j].x = i, blocks[i][j].y = j;
      blocks[i][j].init(blocks[i][j].overall_property, portal_color);
    }

  gravity = -1;

}


/*
   display the whole map
   no input
   no return value
*/
void Map::print(void) {
  for (int i = MAP_R - 1; i >= 0; i--) {
    for (int j = 0; j < MAP_C; j++)
      super_print(content[i][j]);
    printf("\n");
  }
}


/*
   convert the world to the opposite:
    · reverse the direction of world converters
    · swap the color of grounds and air
    · reverse the properties of property grounds and elfins
   input: an object of class Player
   no return value
*/
void Map::converter(Player& u) {
  for (int i = 0; i < MAP_H; i++) {
    for (int j = 0; j < MAP_W; j++) {
      if (blocks[i][j].overall_property / 10 >= 6) { // world converter
        bool flag = false;
        Block block = get_tar_portal(blocks[i][j].overall_property / 10, i, j, flag);
        if (!flag) {
          int k = blocks[i][j].overall_property % 10;
          int serial = blocks[i][j].overall_property / 10;
          int new_direc = 4 * ((k + 1) / 2) - 1 - k;
          blocks[i][j].overall_property = serial * 10 + new_direc;
        }
      }
      else if (blocks[i][j].overall_property / 10 == 2) {
        int k = blocks[i][j].overall_property % 10;
        k = 3 - k;
        blocks[i][j].overall_property = 20 + k;
      }
      fill(blocks[i][j].overall_property, (int*)blocks[i][j].content, u.state, portal_color);
    }
  }

  for (int i = 0; i < elfins.size(); i++) {
    elfins[i].property = 63 - elfins[i].property;
    fill(elfins[i].property, (int*)elfins[i].content, u.state, portal_color);
  }
}


/*
   find the portal that is paired with a certain portal
   input:
    · int variable tar, the property of the certain portal
    · int variables player_xx & player_yy, the block the player is in
    · bool variable flag, whether the portal can be found
   return value:
    · an object of class Block
    · bool variable flag, true if the certain portal is portal, false if it's world converter
*/
Block Map::get_tar_portal(int tar, int player_xx, int player_yy, bool& flag) {
  Block block;
  for (int i = 0; i < MAP_H; i++)
    for (int j = 0; j < MAP_W; j++) {
      if (player_xx == i && player_yy == j) continue; // omit itself
      else if (blocks[i][j].overall_property / 10 == tar) {
        flag = true;
        return blocks[i][j];
      }
    }
  return block;
}


/*
   if the player reaches a gravity converter or a portal/world converter, reverse gravity/deliver the player
   input: an object of class Player
   no return value
*/
void Map::check(Player &u) {
  u.touching_gravity = false;
  int x = u.x, y = u.y;
  int last_x = u.last_x, last_y = u.last_y;
  for (int player_i = x; player_i < x + u.height; player_i++) 
    for (int player_j = y; player_j < y + u.width; player_j++) {
      if (content[player_i][player_j] % 100 == 5) { // gravity converter
        u.touching_gravity = true;
        if (!u.last_touching_gravity) {
          gravity *= -1;
          u.last_touching_gravity = true;
        }
      } 
      else if (content[player_i][player_j] % 100 >= 6 && content[player_i][player_j] % 100 <= 20) { // portal or world converter
        int xx = player_i / BLOCK_H, yy = player_j / BLOCK_W;
        int direc_from = 0; // 0: back    1: front
        Block portal = blocks[xx][yy];
        bool flag = false;
        Block tar_portal = get_tar_portal(content[player_i][player_j] % 100, xx, yy, flag);
        int direc_orig = portal.overall_property % 10;
        if (direc_orig <= 2) { // the original portal is towards up/down 
          if (last_x > x)
            direc_from = direc_orig % 2; // front
          else
            direc_from = 1 - direc_orig % 2; // back
        } 
        else { // the original portal is towards left/right
          if (last_y < y)
            direc_from = direc_orig % 2;
          else
            direc_from = 1 - direc_orig % 2;
        }
        int res_property; // the portal to go
        Block res_portal;
        if (flag) { // portal
          res_property = tar_portal.overall_property % 10;
          res_portal = tar_portal;
        }
        else { // world-converter
          u.state = 1 - u.state;
          converter(u);
          int k = portal.overall_property % 10;
          res_property = 4 * ((k + 1) / 2) - 1 - k;
          res_portal = portal;
        }
        if (res_property <= 2) { // up and down
          if (direc_orig <= 2) {
            double cspeed = u.real_speed;
            if (res_property == direc_orig) { // bounce
              if (u.real_speed != 0)
                cspeed = -0.9 * u.real_speed;
              else
                cspeed = -0.9 * u.speed;
            }
            if (abs(cspeed) <= 1 && abs(cspeed) > 0)
              cspeed = (cspeed / abs(cspeed)) * ceil(abs(cspeed));
            else if (abs(cspeed) > 0)
              cspeed = (cspeed / abs(cspeed)) * floor(abs(cspeed));
            u.speed = cspeed;
            u.real_speed = cspeed;
          }
          u.x = res_portal.x * BLOCK_H + (BLOCK_H / 2 + ((1.5 - res_property) * 2) * ((direc_from - 0.5) * 2) * (u.height * (((res_property % 2) + (direc_from % 2)) % 2) + 2 * (1 - ((res_property % 2) + (direc_from % 2)) % 2)));
          u.y = res_portal.y * BLOCK_W + ((BLOCK_W - u.width) / 2);
        }
        else { // left and right
          u.x = res_portal.x * BLOCK_H + 1;
          u.y = res_portal.y * BLOCK_W + (BLOCK_W / 2 + ((3.5 - res_property) * 2) * ((0.5 - direc_from) * 2) * (u.width * (1 - ((res_property % 2) + (direc_from % 2)) % 2) + 1 * (((res_property % 2) + (direc_from % 2)) % 2)));
        }
        return;
      }
    }
  if (!u.touching_gravity) u.last_touching_gravity = 0;
}


/* update the map content
   input: an object of class Player
   no return value
*/
void Map::update(Player u) {

  for (int i = 0; i < MAP_R; i++)
    for (int j = 0; j < MAP_C; j++)
      content[i][j] = 0;

  for (int r = 0; r < MAP_H; r++)
    for (int c = 0; c < MAP_W; c++)
      for (int i = 0; i < BLOCK_H; i++)
        for (int j = 0; j < BLOCK_W; j++) {
          int x = r * BLOCK_H, y = c * BLOCK_W;
          int cont = blocks[r][c].content[BLOCK_H - i - 1][j];
          if (cont != 0) content[x + i][y + j] = cont;
        }

  //insert elfins into the map
  for (int idx = 0; idx < elfins.size(); idx++)
    for (int i = elfins[idx].x; i < elfins[idx].x + elfins[idx].height; i++) 
      for (int j = elfins[idx].y - 2; j < elfins[idx].y - 2 + elfins[idx].width; j++) 
        if (elfins[idx].content[i - elfins[idx].x][j - elfins[idx].y + 2] % 100 != 0) 
          content[i][j] = elfins[idx].content[i - elfins[idx].x][j - elfins[idx].y + 2]; 

  //insert the player into the map
  for (int i = u.x; i < u.x + u.height; i++)
    for (int j = u.y; j < u.y + u.width; j++)
      content[i][j] = u.content[i - u.x][j - u.y]; 
}

