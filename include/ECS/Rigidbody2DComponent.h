
#ifndef RIGIDBODY_2D_COMPONENT_H
#define RIGIDBODY_2D_COMPONENT_H

#include "../box2d/box2d.h"
#include "../globals.h"
#include "ecs.h"
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class RigidBody2DComponent : public Component {
public:
  RigidBody2DComponent() = default;

  RigidBody2DComponent(bool isDynamic, int x, int y) {
    b2BodyDef bodyDef;
    bodyDef.type = isDynamic ? b2_dynamicBody : b2_staticBody;
    bodyDef.position.Set((float)x, (float)y);
    body = boxworld.CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;

    body->CreateFixture(&fixtureDef);

    vector = body->GetPosition();
  }

  void SetTransform(b2Vec2 vec, float ang) { body->SetTransform(vec, ang); }

  int GetX() {
    b2Vec2 pos = body->GetPosition();
    return pos.x;
  }

  int GetY() {
    b2Vec2 pos = body->GetPosition();
    return pos.y;
  }

  b2Body *GetBody() { return body; }

  void update() override { b2Vec2 pos = body->GetPosition(); }

private:
  b2Body *body;
  b2Vec2 vector;
};

#endif
