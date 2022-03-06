#include "map.h"
#include "utils.h"

#include <cstdio>
#include <iostream>

int main() {
    
  Map map;
  map.init(30, 80); // 之后要改为从地图初始化

  map.print();

  return 0;

}
