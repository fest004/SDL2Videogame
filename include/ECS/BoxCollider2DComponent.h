#ifndef BOX_COLLIDER_2D_COMPONENT_H
#define BOX_COLLIDER_2D_COMPONENT_H

#include "../box2d/box2d.h"
#include "../globals.h"
#include "Rigidbody2DComponent.h"
#include "ecs.h"
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <iostream>

class BoxCollider2DComponent : public Component {
public:
  BoxCollider2DComponent(std::string t) { tag = t; }
  ~BoxCollider2DComponent() = default;

  void init() override {
    colliderScale = 1;
    rigidbody = entity->getComponent<RigidBody2DComponent>();

    m_body = rigidbody.GetBody();

    m_shape.SetAsBox(1.0f, 1.0f);
    m_fixtureDef.shape = &m_shape;
    m_fixtureDef.density = 1.0f;
    m_fixtureDef.friction = 0.5f;
    m_fixtureDef.restitution = 0.0f;
    m_body->CreateFixture(&m_fixtureDef);
  }

  BoxCollider2DComponent(const BoxCollider2DComponent &) = default;

  void SetWidthAndHeight(float width, float height) {
    m_shape.SetAsBox(width * colliderScale, height * colliderScale);
    m_fixtureDef.shape = &m_shape;
  }

  void update() override {
    m_body->SetTransform(b2Vec2(rigidbody.GetX(), rigidbody.GetY()), 0.0f);
  }

  int GetWidth() {
    // return m_shape.m_vertices[1].x * 2 * colliderScale;
    return 32;
  }
  int GetHeight() {
    // return m_shape.m_vertices[2].y * 2 * colliderScale;
    return 32;
  }

  void DrawOutline(SDL_Renderer *renderer) {
    // Get the Box2D polygon shape attached to the body
    b2Fixture *fixture = m_body->GetFixtureList();
    b2Shape *shape = fixture->GetShape();
    b2PolygonShape *polygonShape = dynamic_cast<b2PolygonShape *>(shape);

    // Get the position of the body that the polygon shape is attached to
    b2Vec2 position = m_body->GetPosition();

    // Get the size of the polygon shape in pixels
    SDL_Point size = GetSize(polygonShape->m_vertices, polygonShape->m_count);

    // Define the SDL_Rect object that represents the rectangle to draw
    SDL_Rect rect = {(int)position.x - size.x / 2, (int)position.y - size.y / 2,
                     size.x, size.y};

    // Set the drawing color to red
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    // Draw the rectangle on the screen
    SDL_RenderDrawRect(renderer, &rect);
  }

  int GetScale() { return colliderScale; }

  void SetScale(int sc) { colliderScale = sc; }

private:
  b2BodyDef m_bodyDef;
  b2Body *m_body;
  b2PolygonShape m_shape;
  b2FixtureDef m_fixtureDef;
  int colliderScale;
  RigidBody2DComponent rigidbody;
  std::string tag;

  SDL_Point GetSize(b2Vec2 *vertices, int32 count) {
    // Find the minimum and maximum x and y values of the vertices
    float minX = vertices[0].x;
    float maxX = vertices[0].x;
    float minY = vertices[0].y;
    float maxY = vertices[0].y;
    for (int32 i = 1; i < count; i++) {
      if (vertices[i].x < minX)
        minX = vertices[i].x;
      if (vertices[i].x > maxX)
        maxX = vertices[i].x;
      if (vertices[i].y < minY)
        minY = vertices[i].y;
      if (vertices[i].y > maxY)
        maxY = vertices[i].y;
    }
    // Calculate the width and height of the bounding box
    int width = (int)((maxX - minX) * 30.0f);
    int height = (int)((maxY - minY) * 30.0f);

    // Return the size as a SDL_Point object
    return SDL_Point{width, height};
  }
};
#endif

// #ifndef BOX_COLLIDER_2D_COMPONENT_H
// #define BOX_COLLIDER_2D_COMPONENT_H
//
// #include "../box2d/box2d.h"
// #include "../globals.h"
// #include "Rigidbody2DComponent.h"
// #include "ecs.h"
// #include <iostream>
//
// class BoxCollider2DComponent : public Component {
// public:
//   // glm::vec2 Offset = {0.0f, 0.0f};
//   // glm::vec2 Size = {0.0f, 0.0f};
//   //
//   // // storage for runtime
//   // void *RuntimeFixture = nullptr;
//   //
//   BoxCollider2DComponent(std::string t) { tag = t; }
//   ~BoxCollider2DComponent() = default;
//
//   void init() override {
//     // if (!entity->hasComponent<RigidBody2DComponent>()) {
//     //   entity->addComponent<RigidBody2DComponent>();
//     // }
//     //
//     scale = 1;
//
//     rigidbody = entity->getComponent<RigidBody2DComponent>();
//
//     m_body = rigidbody.GetBody();
//
//     m_shape.SetAsBox(0.32, 0.32);
//     m_fixtureDef.shape = &m_shape;
//     m_fixtureDef.density = 1.0f;
//     m_fixtureDef.friction = 0.5f;
//     m_fixtureDef.restitution = 0.0f;
//     // m_body->CreateFixture(&m_fixtureDef);
//   }
//   BoxCollider2DComponent(const BoxCollider2DComponent &) = default;
//
//   void SetWidthAndHeight(int width, int height) {
//     m_shape.SetAsBox(width * scale, height * scale);
//     m_fixtureDef.shape = &m_shape;
//   }
//
//   void update() override {
//     // std::cout << rigidbody.GetX() << std::endl;
//     // std::cout << rigidbody.GetY() << std::endl;
//     m_body->SetTransform(b2Vec2(rigidbody.GetX(), rigidbody.GetY()), 0.0f);
//   }
//
//   SDL_Point GetSize(b2Vec2 *vertices, int32 count) {
//     // Find the minimum and maximum x and y values of the vertices
//     float minX = vertices[0].x;
//     float maxX = vertices[0].x;
//     float minY = vertices[0].y;
//     float maxY = vertices[0].y;
//     for (int32 i = 1; i < count; i++) {
//       if (vertices[i].x < minX)
//         minX = vertices[i].x;
//       if (vertices[i].x > maxX)
//         maxX = vertices[i].x;
//       if (vertices[i].y < minY)
//         minY = vertices[i].y;
//       if (vertices[i].y > maxY)
//         maxY = vertices[i].y;
//     }
//
//     // Calculate the width and height of the bounding box
//     int width = (int)((maxX - minX) * 30.0f);
//     int height = (int)((maxY - minY) * 30.0f);
//
//     // Return the size as a SDL_Point object
//     return SDL_Point{width, height};
//   }
//
//   int GetWidth() { return 32; }
//   int GetHeight() { return 32; }
//
//   void DrawOutline(SDL_Renderer *renderer) {
//     // Get the Box2D polygon shape attached to the body
//     b2Fixture *fixture = m_body->GetFixtureList();
//     b2Shape *shape = fixture->GetShape();
//     b2PolygonShape *polygonShape = dynamic_cast<b2PolygonShape *>(shape);
//
//     // Get the position of the body that the polygon shape is attached to
//     b2Vec2 position = m_body->GetPosition();
//
//     // Get the size of the polygon shape in pixels
//     SDL_Point size = GetSize(polygonShape->m_vertices,
//     polygonShape->m_count);
//
//     // Define the SDL_Rect object that represents the rectangle to draw
//     SDL_Rect rect = {(int)position.x - size.x / 2, (int)position.y - size.y /
//     2,
//                      size.x, size.y};
//
//     // Set the drawing color to red
//     SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
//
//     // Draw the rectangle on the screen
//     SDL_RenderDrawRect(renderer, &rect);
//   }
//
//   int GetScale() {
//     // return scale;
//     return 1;
//   }
//
//   void SetScale(int sc) { scale = sc; }
//
// private:
//   b2BodyDef m_bodyDef;
//   b2Body *m_body;
//   b2PolygonShape m_shape;
//   b2FixtureDef m_fixtureDef;
//   int scale;
//   RigidBody2DComponent rigidbody;
//   std::string tag;
// };
//
// #endif
