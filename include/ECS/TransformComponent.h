#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

#include "../Vector2D.h"
#include "ecs.h"

class TransformComponent : public Component {
public:
  Vector2D position;
  Vector2D velocity;

  int speed = 10;

  int height = 32;
  int width = 32;
  int scale = 1;

  TransformComponent() { position.Zero(); }
  ~TransformComponent() = default;

  TransformComponent(int sc) {
    position.Zero();
    scale = sc;
  }

  TransformComponent(float x, float y) {
    position.x = x;
    position.y = y;
  }

  TransformComponent(float x, float y, int h, int w, int sc) {
    position.x = x;
    position.y = y;
    height = h;
    width = w;
    scale = sc;
  }

  void init() override {
    //
    velocity.Zero();
  }

  void update() override {
    position.x += velocity.x * speed;
    position.y += velocity.y * speed;
  }
};

#endif
