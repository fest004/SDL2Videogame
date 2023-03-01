#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

#include "../Vector2D.h"
#include "ecs.h"

class TransformComponent : public Component {
public:
  Vector2D position;

  TransformComponent() {
    position.x = 0.0f;
    position.y = 0.0f;
  }

  TransformComponent(float x, float y) {
    position.x = x;
    position.y = y;
  }

  void init() override {
    // xpos = 0;
    // ypos = 0;
  }

  void update() override {}
};

#endif
