#ifndef WORLD_H
#define WORLD_H

#include "box2d/box2d.h"

class BoxWorld {
public:
  void OnRuntimeStart();
  void OnRuntimeStop();
  b2World GetBoxWorld();

private:
  b2World *m_Box2DPhysicsWorld = nullptr;
};

#endif
