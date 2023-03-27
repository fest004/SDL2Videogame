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

  RigidBody2DComponent(const bool &isDynamic, int x, int y)
      : body(nullptr), vector(0.0f, 0.0f) {
    b2BodyDef bodyDef;
    bodyDef.type = isDynamic ? b2_dynamicBody : b2_staticBody;
    bodyDef.position.Set(static_cast<float>(x), static_cast<float>(y));
    body = boxworld.CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;

    body->CreateFixture(&fixtureDef);

    vector = body->GetPosition();
  }

  void SetTransform(const b2Vec2 &vec, const float &ang) {
    body->SetTransform(vec, ang);
  }

  int GetX() const {
    b2Vec2 pos = body->GetPosition();
    return pos.x;
  }

  int GetY() const {
    b2Vec2 pos = body->GetPosition();
    return pos.y;
  }

  b2Body *GetBody() const { return body; }

  void update() override {
    b2Vec2 pos = body->GetPosition();
    vector = b2Vec2(pos.x * 30.0f, pos.y * 30.0f);
  }

private:
  b2Body *body;
  b2Vec2 vector;
};

#endif
