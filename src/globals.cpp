#include "../include/globals.h"
#include "../include/box2d/box2d.h"
#include <iostream>

void initBox() {
  MyContactListener contactListener;
  boxworld.SetAllowSleeping(false);
  boxworld.SetContactListener(&contactListener);
  std::cout << "ContactListener Set" << std::endl;
}
