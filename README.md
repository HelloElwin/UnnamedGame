# UnnamedGame

## Team members

Li Han (3035845954) [@Kelios1556](https://github.com/Kelios1556)

Ye Yaowen (3035845344) [@HelloElwin](https://github.com/HelloElwin)

## Introduction

"Unnamed Game is a fun game without a name (yet)! And you, the bravest explorer in HKU, is given the job to find the name for this game! The name is hidden in a secrete room in a world of ice and flame, and your journey starts at a certain point in this world. At the end point lies the entrance of the secrete room and your ultimate goal: name for the Unnamed Game!"

This is a keyboard-based adventure game for one player controlled by **WASD**. The player is suggested to kick in a way to move itself to the destination.

A list of features including portals, gravity switches, world-converters etc., are designed to assist the travel. Two properties, ice and frame, are attached to the player, bars and grounds. Under opposite properties, bars and grounds may be dangerous to the player.

Success means safely arriving at the endpoint. 

## Element Description

### Air

The player will fall/flow according the direction of gravity.

### Bar

It can move in horizontal directions with a property of ice or flame. A bar will move towards the player when the player arrives at the same layer. If the player holds the same property as the bar's, the bar is equivalent to Air. However, if the player holds the opposite property as the bar's, direct contacting means **Game Fails**.

### Gravity Switch

When the player reaches a Gravity Switch, the direction of gravity will be changed.

### Inner World

When the player enter a World Converter from the external world, the player will arrive in the inner world. The properties of some features (e.g., player, bars, property grounds) may convert upon player's arrival.

### Portal

Portals, appeared in pairs, are distinguished by colors. When the player enter a portal from one side, the player will be sent to the same side of another portal with the same color.

### Property Ground

They differd from normal grounds as their specified properties. They may be attached with ice or flame as their own property, which might convert to the opposite properties in the inner world. If the player is with the same property as the ground, it can be treated as the normal ground. Nevertheless, walking on the ground with the opposite property will result in **Game Fails**.

### World Converter

World converters usually have similar shapes with portals except that they are not appear in pairs. It means that if there's no other portal that is with the same color as this "portal", then it is a world converter. When it is a necessity to pass a block of property ground with the opposite property, or when facing the coming attack from a bar with the opposite property, the player can enter the external/inner world through these world converters.  

## Features

1. Generation of random game sets or events

    * We use seed to randomly generate 

2. Data structures for storing game status

    * 


3. Dynamic memory management


4. File input/output (e.g., for loading/saving game status)


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


## Usage

Start the game with these commands:

```bash
make clean
make main
./main
```



