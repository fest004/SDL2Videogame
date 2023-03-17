#ifndef BOX_COLLIDER_2D_COMPONENT_H
#define BOX_COLLIDER_2D_COMPONENT_H

#include "../box2d/box2d.h"
#include "Rigidbody2DComponent.h"
#include "ecs.h"
#include <glm/glm.hpp>
#include <iostream>

class BoxCollider2DComponent : public Component {
public:
  // glm::vec2 Offset = {0.0f, 0.0f};
  // glm::vec2 Size = {0.0f, 0.0f};
  //
  // // storage for runtime
  // void *RuntimeFixture = nullptr;
  //
  BoxCollider2DComponent() = default;
  ~BoxCollider2DComponent() = default;

  void init() override {
    // if (!entity->hasComponent<RigidBody2DComponent>()) {
    //   entity->addComponent<RigidBody2DComponent>();
    // }
    //
    scale = 1;

    std::cout << "Program made it here bitches" << std::endl;

    rigidbody = entity->getComponent<RigidBody2DComponent>();

    m_body = rigidbody.GetBody();

    std::cout << rigidbody.GetX() << std::endl;
    std::cout << rigidbody.GetY() << std::endl;
    std::cout << std::endl;
    m_shape.SetAsBox(32, 32);
    m_fixtureDef.shape = &m_shape;
    m_fixtureDef.density = 1.0f;
    m_fixtureDef.friction = 0.5f;
    m_fixtureDef.restitution = 0.0f;
  }
  BoxCollider2DComponent(const BoxCollider2DComponent &) = default;

  void SetWidthAndHeight(int width, int height) {
    m_shape.SetAsBox(width * scale, height * scale);
    m_fixtureDef.shape = &m_shape;
  }

  void update() override {
    // std::cout << rigidbody.GetX() << std::endl;
    // std::cout << rigidbody.GetY() << std::endl;
    // m_body->SetTransform(b2Vec2(rigidbody.GetX(), rigidbody.GetY()), 0.0f);
  }

  // float GetWidth() {
  //         b2PolygonShape* shape =
  //         static_cast<b2PolygonShape*>(fixture->GetShape()); b2Vec2 size =
  //         shape->GetVertex(2) - shape->GetVertex(0); return size.x;
  //     }
  //

  int GetWidth() {
    // int width = abs(m_shape.m_vertices[2].x) - abs(m_shape.m_vertices[0].x);
    return 32;
  }

  int GetHeight() {
    // int height = abs(m_shape.m_vertices[2].y) - abs(m_shape.m_vertices[0].y);
    return 32;
  }

  int GetScale() {
    // return scale;
    return 1;
  }

  void SetScale(int sc) { scale = sc; }

private:
  b2BodyDef m_bodyDef;
  b2Body *m_body;
  b2PolygonShape m_shape;
  b2FixtureDef m_fixtureDef;
  int scale;
  RigidBody2DComponent rigidbody;
};

#endif
