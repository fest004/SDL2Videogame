#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "../textureManager.h"
#include "BoxCollider2DComponent.h"
#include "Rigidbody2DComponent.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

class SpriteComponent : public Component {
public:
  // SpriteComponent() = default;

  SpriteComponent(const char *path) {
    texture = textureManager::loadTexture(path);
  }
  ~SpriteComponent() { SDL_DestroyTexture(texture); }

  void setTexture(const char *path) {

    texture = textureManager::loadTexture(path);
  }

  void init() override {
    rigidbody = &entity->getComponent<RigidBody2DComponent>();

    sourceRectangle.x = 0;
    sourceRectangle.y = 0;
    sourceRectangle.w = boxcollider->GetWidth();
    sourceRectangle.h = boxcollider->GetHeight();
  }

  void update() override {
    destinationRect.x = static_cast<int>(rigidbody->GetX());
    destinationRect.y = static_cast<int>(rigidbody->GetY());
    destinationRect.w = boxcollider->GetWidth() * boxcollider->GetScale();
    destinationRect.h = boxcollider->GetHeight() * boxcollider->GetScale();
  }

  void draw() override {
    textureManager::DrawTexture(texture, sourceRectangle, destinationRect);
  }

private:
  RigidBody2DComponent *rigidbody;
  BoxCollider2DComponent *boxcollider;
  SDL_Texture *texture;
  SDL_Rect sourceRectangle, destinationRect;
};

#endif
