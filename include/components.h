#include "ecs.h"

class PositionComponent : public Component {
public:
  int GetX() { return xpos; }
  int GetY() { return ypos; }

  void init() override {
    xpos = 0;
    ypos = 0;
  }

  void update() override {
    xpos++;
    ypos++;
  }

  void setPos(int x, int y) {
    xpos = x;
    ypos = y;
  }

private:
  int xpos = 0;
  int ypos = 0;
};
