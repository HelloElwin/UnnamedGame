#ifndef MAP_H
#define MAP_H

class Map {
  public:
    void init(int, int);
    void print(void);
    void update(void);
  private:
    int row;
    int col;
    int state; // 0 for Outer World and 1 for Inner World
    int content[200][200];
};

#endif
