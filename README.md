# UnnamedGame

## Team members

Li Han (3035845954) [@Kelios1556](https://github.com/Kelios1556)

Ye Yaowen (3035845344) [@HelloElwin](https://github.com/HelloElwin)

## Introduction

"Unnamed Game is a fun game without a name (yet)! And you, the bravest explorer in HKU, are given the job to find the name for this game! The name is hidden in a secrete room in a world of ice and flame, and your journey starts from a certain point in this world. At the end point lies the entrance of the secrete room and your ultimate goal: name for the Unnamed Game!"

This is a keyboard-based adventure game for one player controlled by **WASD**. The player is suggested to kick in a way to travel to the destination.

A list of features including portals, gravity switches, world converters etc., are designed to assist the travel. Two properties, ice and flame, are attached to the player, bars and grounds. Under opposite properties, bars and grounds may be dangerous to the player.

## Quick Start

Start the game with these commands!

```bash
make clean
make main
./main
```

## Element Description

### Air

The player will fall/float according the direction of gravity.

### Bar

It can move in horizontal directions with a property of ice or flame. A bar will move towards the player when the player arrives at the same level. If the player holds the same property as the bar, the bar is equivalent to Air. Otherwise, if the player holds the opposite property as the bar's, direct contacting means **Game Fails**.

### Gravity Switch

When the player reaches a Gravity Switch, the direction of gravity will be changed.

### Inner World

When the player enters a World Converter from the external world, the player will arrive in the inner world, and vice versa. The properties of some features (e.g., player, bars, property grounds) may convert upon player's arrival.

### Portal

Portals, appearing in pairs, are distinguished by colors. When the player enters a portal from one side, the player will be sent to the same side of another portal with the same color.

### Property Ground

They differd from normal grounds as their specified properties. They may be attached with ice or flame as their own property, which might convert to the opposite properties in the inner world. If the player is with the same property as the ground, it can be treated as the normal ground. Otherwise, walking on the ground with the opposite property will result in **Game Fails**.

### World Converter

World converters usually have similar shapes with portals except that they are not appear in pairs. It means that if there's no other portal that is with the same color as this "portal", then it is a world converter. When it is a necessity to pass a block of property ground with the opposite property, or when facing the coming attack from a bar with the opposite property, the player can enter the external/inner world through these world converters.  

## Features

1. Generation of random game sets or events

    * We use random seeds to decide the color of Portals and World-Converters.

2. Data structures for storing game status

    * We design a class `Map` to store the information of the map.
    * We design a class `Block` to store the information of blocks, i.e. ground, portals etc. 
    * We design a class `Player` to store the information of the player.

3. Dynamic memory management

    * We allocate new memory for blocks in a map when the player enters it, and deallocate the memory upon end of game in this map.

4. File input/output (e.g., for loading/saving game status)

    * Before the game, the player needs to input a number to choose a map available.
    * The movement of the player is controlled by keyboard inputs **WASD**.

5. Program codes in multiple files
```
.
├── Makefile
├── README.md
├── bin
│   ├── *.o
├── lib
│   ├── blocks
│   └── maps
├── main
├── src
│   ├── *.h
│   ├── *.cpp
└── test
    ├── color_test.py
    ├── map_test.py
    └── testfill.cpp
```

6. Program functions

   **Initialize the map**
   
   ```c++
   void Map::init(int map_num);
   ```

   **Print the whole map**

   ```c++
   void Map::print(void);
   ```

   **Update map**
   
   ```c++
   void Map::update(Player u);
   ```
   
   **Portal delivery**
   
   ```c++
   void Map::check(Player &u);
   ```





